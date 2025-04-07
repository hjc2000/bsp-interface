#include "heap.h"
#include <base/RentedPtrFactory.h>
#include <base/string/define.h>
#include <bsp-interface/di/interrupt.h>
#include <bsp-interface/di/task.h>
#include <vector>

namespace
{
	// 这里使用裸指针，确保 C++ 的全局对象的构造函数访问到此变量时，此变量已经初始化完成了。
	// 因为它在 C 的启动代码中被初始化，这发生在 C++ 启动代码之前。
	//
	// 这可以确保 C++ 全局对象构造函数如果涉及到动态内存分配，在构造函数中访问此变量时，此变量
	// 已经初始化完成。随后在堆上构造 std::vector<std::shared_ptr<bsp::IHeap>> 对象将此变量
	// 赋值为指向堆上 std::vector<std::shared_ptr<bsp::IHeap>> 对象的指针后不会被启动代码
	// 赋值为 nullptr.
	std::vector<std::shared_ptr<bsp::IHeap>> *volatile _heap_vector = nullptr;

} // namespace

/* #region AddHeap */

void bsp::di::heap::AddHeap(std::shared_ptr<bsp::IHeap> const &heap)
{
	bsp::di::task::TaskGuard g;
	if (_heap_vector == nullptr)
	{
		std::vector<std::shared_ptr<bsp::IHeap>> *vec = new std::vector<std::shared_ptr<bsp::IHeap>>{};
		vec->push_back(heap);
		vec->push_back(base::RentedPtrFactory::Create(&bsp::di::heap::Heap()));
		_heap_vector = vec;
		return;
	}

	_heap_vector->push_back(heap);
}

void bsp::di::heap::AddHeap(uint8_t *buffer, size_t size)
{
	bsp::di::task::TaskGuard g;
	bsp::di::heap::AddHeap(bsp::di::heap::CreateHeap(buffer, size));
}

void bsp::di::heap::AddHeap(base::Span const &span)
{
	bsp::di::task::TaskGuard g;
	AddHeap(span.Buffer(), span.Size());
}

/* #endregion */

void *bsp::di::heap::Malloc(size_t size) noexcept
{
	bsp::di::task::TaskGuard g;
	if (_heap_vector == nullptr)
	{
		void *p = bsp::di::heap::Heap().Malloc(size);
		return p;
	}

	for (std::shared_ptr<bsp::IHeap> &heap : *_heap_vector)
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
	bsp::di::task::TaskGuard g;
	if (_heap_vector == nullptr)
	{
		bsp::di::heap::Heap().Free(ptr);
		return;
	}

	for (std::shared_ptr<bsp::IHeap> &heap : *_heap_vector)
	{
		if (ptr >= heap->begin() && ptr < heap->end())
		{
			heap->Free(ptr);
			return;
		}
	}
}
