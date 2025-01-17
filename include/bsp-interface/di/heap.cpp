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

void *operator new(size_t size)
{
	bsp::di::task::TaskGuard g;
	if (_heap_vector == nullptr)
	{
		void *ptr = bsp::di::heap::Heap().Malloc(size);
		if (ptr == nullptr)
		{
			throw std::bad_alloc{};
		}

		return ptr;
	}

	for (std::shared_ptr<bsp::IHeap> &heap : *_heap_vector)
	{
		void *ptr = heap->Malloc(size);
		if (ptr != nullptr)
		{
			return ptr;
		}
	}

	throw std::bad_alloc{};
}

void *operator new[](size_t size)
{
	bsp::di::task::TaskGuard g;
	if (_heap_vector == nullptr)
	{
		void *ptr = bsp::di::heap::Heap().Malloc(size);
		if (ptr == nullptr)
		{
			throw std::bad_alloc{};
		}

		return ptr;
	}

	for (std::shared_ptr<bsp::IHeap> &heap : *_heap_vector)
	{
		void *ptr = heap->Malloc(size);
		if (ptr != nullptr)
		{
			return ptr;
		}
	}

	throw std::bad_alloc{};
}

void *operator new(size_t size, std::nothrow_t const &) noexcept
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

void *operator new[](size_t size, std::nothrow_t const &) noexcept
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

void operator delete(void *ptr) noexcept
{
	if (ptr == nullptr)
	{
		return;
	}

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

void operator delete[](void *ptr) noexcept
{
	if (ptr == nullptr)
	{
		return;
	}

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

void operator delete(void *ptr, std::nothrow_t const &) noexcept
{
	if (ptr == nullptr)
	{
		return;
	}

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

void operator delete[](void *ptr, std::nothrow_t const &) noexcept
{
	if (ptr == nullptr)
	{
		return;
	}

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

void operator delete(void *ptr, size_t size) noexcept
{
	if (ptr == nullptr)
	{
		return;
	}

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

void operator delete[](void *ptr, size_t size) noexcept
{
	if (ptr == nullptr)
	{
		return;
	}

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

void DI_AddHeap(std::shared_ptr<bsp::IHeap> const &heap)
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

void DI_AddHeap(uint8_t *buffer, size_t size)
{
	bsp::di::task::TaskGuard g;
	DI_AddHeap(bsp::di::heap::CreateHeap(buffer, size));
}
