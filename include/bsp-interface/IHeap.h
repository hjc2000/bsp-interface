#pragma once
#include <stddef.h>
#include <stdint.h>

namespace bsp
{
	/// @brief 堆接口。
	class IHeap
	{
	public:
		virtual void *Malloc(size_t size) = 0;
		virtual void Free(void *p) = 0;

		/// @brief 堆的起点。
		/// @return
		virtual uint8_t *begin() = 0;

		/// @brief 堆的最后一个字节再 +1.
		/// @return
		virtual uint8_t *end() = 0;

		/// @brief 堆的总大小。
		/// @return
		size_t TotalSize() const
		{
			IHeap *self = const_cast<IHeap *>(this);
			return self->end() - self->begin();
		}

		/// @brief 剩余的自由空间。单位：字节。
		/// @note 不一定是一整块连续的，有可能是碎片化的。
		/// @return
		virtual size_t RemainingFreeSize() const = 0;
	};
} // namespace bsp
