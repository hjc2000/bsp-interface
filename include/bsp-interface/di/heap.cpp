#include "heap.h"
#include <bsp-interface/di/interrupt.h>

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
