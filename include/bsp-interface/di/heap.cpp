#include "heap.h"
#include "base/RentedPtrFactory.h"
#include "base/task/task.h"
#include <vector>

namespace
{
	// 这里使用裸指针，确保 C++ 的全局对象的构造函数访问到此变量时，此变量已经初始化完成了。
	// 因为它在 C 的启动代码中被初始化，这发生在 C++ 启动代码之前。
	//
	// 这可以确保 C++ 全局对象构造函数如果涉及到动态内存分配，在构造函数中访问此变量时，此变量
	// 已经初始化完成。随后在堆上构造 std::vector<std::shared_ptr<base::heap::IHeap>> 对象将此变量
	// 赋值为指向堆上 std::vector<std::shared_ptr<base::heap::IHeap>> 对象的指针后不会被启动代码
	// 赋值为 nullptr.
	//
	// 动态内存分配有可能被 C++ 全局对象的构造函数使用，如果这里使用的不是 C 的原始类型，即 std::vector
	// 的裸指针，而是使用C++ 的 std::vector 对象的话，就会造成 “一个全局对象依赖另一个全局对象”，而 C++
	// 全局对象的构造顺序是未定义的，会发生错误。
	//
	// 所以这里使用裸指针，并用延迟初始化技术，在需要时才在堆上构造 std::vector 对象并让此指针指向它。
	std::vector<std::shared_ptr<base::heap::IHeap>> *volatile _heap_vector = nullptr;

} // namespace

/* #region AddHeap */

void bsp::di::heap::AddHeap(std::shared_ptr<base::heap::IHeap> const &heap)
{
	base::task::TaskSchedulerSuspendGuard g;
	if (_heap_vector == nullptr)
	{
		std::vector<std::shared_ptr<base::heap::IHeap>> *vec = new std::vector<std::shared_ptr<base::heap::IHeap>>{};
		vec->push_back(heap);
		vec->push_back(base::RentedPtrFactory::Create(&bsp::di::heap::Heap()));
		_heap_vector = vec;
		return;
	}

	_heap_vector->push_back(heap);
}

void bsp::di::heap::AddHeap(uint8_t *buffer, size_t size)
{
	base::task::TaskSchedulerSuspendGuard g;
	bsp::di::heap::AddHeap(bsp::di::heap::CreateHeap(buffer, size));
}

void bsp::di::heap::AddHeap(base::Span const &span)
{
	base::task::TaskSchedulerSuspendGuard g;
	AddHeap(span.Buffer(), span.Size());
}

/* #endregion */

void *bsp::di::heap::Malloc(size_t size) noexcept
{
	base::task::TaskSchedulerSuspendGuard g;
	if (_heap_vector == nullptr)
	{
		void *p = bsp::di::heap::Heap().Malloc(size);
		return p;
	}

	for (std::shared_ptr<base::heap::IHeap> &heap : *_heap_vector)
	{
		void *ptr = heap->Malloc(size);
		if (ptr != nullptr)
		{
			return ptr;
		}
	}

	return nullptr;
}

void bsp::di::heap::Free(void *ptr) noexcept
{
	base::task::TaskSchedulerSuspendGuard g;
	if (_heap_vector == nullptr)
	{
		bsp::di::heap::Heap().Free(ptr);
		return;
	}

	for (std::shared_ptr<base::heap::IHeap> &heap : *_heap_vector)
	{
		if (ptr >= heap->begin() && ptr < heap->end())
		{
			heap->Free(ptr);
			return;
		}
	}
}
