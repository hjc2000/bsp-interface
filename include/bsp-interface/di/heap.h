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
			///
			/// @brief 获取主堆。
			///
			/// @warning 返回的对象必须是函数内部的 static 变量，并且使用 PREINIT 先
			/// 调用一次，保证在 main 函数之前已经初始化过了。
			///
			/// @warning 禁止在全局中定义 bsp::IHeap 变量然后返回这个变量，
			/// 因为全局变量的构造顺序是不确定的。其他全局对象很有可能依赖动态内存分配。
			///
			/// @return
			///
			bsp::IHeap &Heap();

			std::shared_ptr<bsp::IHeap> CreateHeap(uint8_t *buffer, size_t size);

			/* #region AddHeap */

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

			/* #endregion */

			void *Malloc(size_t size) noexcept;

			void Free(void *ptr) noexcept;
		} // namespace heap
	} // namespace di
} // namespace bsp
