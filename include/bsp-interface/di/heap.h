#pragma once
#include <base/stream/Span.h>
#include <bsp-interface/IHeap.h>
#include <cstddef>
#include <memory>

namespace bsp
{
	namespace di
	{
		namespace heap
		{
			/// @brief 获取主堆。
			/// @return
			bsp::IHeap &Heap();

			std::shared_ptr<bsp::IHeap> CreateHeap(uint8_t *buffer, size_t size);

#pragma region 已经实现
			/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
			/// @param heap
			void AddHeap(std::shared_ptr<bsp::IHeap> const &heap);

			/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
			/// @param buffer
			/// @param size
			void AddHeap(uint8_t *buffer, size_t size);

			/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
			/// @param span
			void AddHeap(base::Span const &span);
#pragma endregion

			void *Malloc(size_t size) noexcept;

			void Free(void *ptr) noexcept;
		} // namespace heap
	} // namespace di
} // namespace bsp
