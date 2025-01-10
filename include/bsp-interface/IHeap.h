#pragma once
#include <stddef.h>
#include <stdint.h>

namespace bsp
{
	class IHeap
	{
	public:
		virtual void *Malloc(size_t size) = 0;
		virtual void Free(void *p) = 0;
	};
} // namespace bsp
