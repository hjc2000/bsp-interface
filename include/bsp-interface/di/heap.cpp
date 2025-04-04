#include "heap.h"
#include <base/RentedPtrFactory.h>
#include <base/string/define.h>
#include <bsp-interface/di/interrupt.h>
#include <bsp-interface/di/task.h>
#include <vector>

namespace
{
	std::vector<std::shared_ptr<bsp::IHeap>> *volatile _heap_vector = nullptr;
}

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
