#include "heap.h"
#include <base/RentedPtrFactory.h>
#include <bsp-interface/di/interrupt.h>
#include <vector>

namespace
{
	std::vector<std::shared_ptr<bsp::IHeap>> *_heap_vector = nullptr;
}

void *operator new(size_t size)
{
	bsp::GlobalInterruptGuard g;
	void *ptr = DI_Heap().Malloc(size);
	if (ptr == nullptr)
	{
		throw std::bad_alloc{};
	}

	return ptr;
}

void *operator new[](size_t size)
{
	bsp::GlobalInterruptGuard g;
	void *ptr = DI_Heap().Malloc(size);
	if (ptr == nullptr)
	{
		throw std::bad_alloc{};
	}

	return ptr;
}

void *operator new(size_t size, std::nothrow_t const &) noexcept
{
	bsp::GlobalInterruptGuard g;
	void *p = DI_Heap().Malloc(size);
	if (p == nullptr)
	{
	}

	return p;
}

void *operator new[](size_t size, std::nothrow_t const &) noexcept
{
	bsp::GlobalInterruptGuard g;
	void *p = DI_Heap().Malloc(size);
	if (p == nullptr)
	{
	}

	return p;
}

void operator delete(void *ptr) noexcept
{
	bsp::GlobalInterruptGuard g;
	DI_Heap().Free(ptr);
}

void operator delete[](void *ptr) noexcept
{
	bsp::GlobalInterruptGuard g;
	DI_Heap().Free(ptr);
}

void operator delete(void *ptr, std::nothrow_t const &) noexcept
{
	bsp::GlobalInterruptGuard g;
	DI_Heap().Free(ptr);
}

void operator delete[](void *ptr, std::nothrow_t const &) noexcept
{
	bsp::GlobalInterruptGuard g;
	DI_Heap().Free(ptr);
}

void operator delete(void *ptr, size_t size) noexcept
{
	bsp::GlobalInterruptGuard g;
	DI_Heap().Free(ptr);
}

void operator delete[](void *ptr, size_t size) noexcept
{
	bsp::GlobalInterruptGuard g;
	DI_Heap().Free(ptr);
}

void DI_AddHeap(std::shared_ptr<bsp::IHeap> const &heap)
{
	bsp::GlobalInterruptGuard g;
	if (_heap_vector == nullptr)
	{
		_heap_vector = new std::vector<std::shared_ptr<bsp::IHeap>>{};
		_heap_vector->push_back(base::RentedPtrFactory::Create(&DI_Heap()));
	}

	_heap_vector->push_back(heap);
}
