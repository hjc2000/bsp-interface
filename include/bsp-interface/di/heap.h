#pragma once
#include <bsp-interface/IHeap.h>
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
			void AddHeap(std::shared_ptr<bsp::IHeap> const &heap);
			void AddHeap(uint8_t *buffer, size_t size);
#pragma endregion
		} // namespace heap
	} // namespace di
} // namespace bsp
