#pragma once
#include <stddef.h>
#include <stdint.h>

namespace bsp
{
	namespace di
	{
		namespace cache
		{
			/// @brief 使能缓存。
			/// @note 会同时使能 D-Cache 和 I-Cache.
			void Enable();

			/// @brief 失能缓存。
			/// @note 会同时失能 D-Cache 和 I-Cache.
			void Disable();

			/// @brief 是 D-Cache 无效。
			/// @note 即将 D-Cache 的数据标记为过期的，重新从内存中读取数据放到 D-Cache 中。
			void InvalidateDCache();

			/// @brief 将指定内存地址处的指定大小的数据进行 D-Cache 无效化。即如果这个地方的数据
			/// 有被 D-Cache 缓存，则将对应的缓存无效化。
			/// @param address
			/// @param size
			void InvalidateDCache(void *address, int32_t size);

			/// @brief 清除 D-Cache。
			/// @note 即将原本从内存中读取到 D-Cache 中，并且已经修改过的 D-Cache 的数据写入
			/// 内存中而不是仅仅停留在 D-Cache 中。
			void CleanDCache();

			/// @brief 清除并且无效化 D-Cache.
			void CleanAndInvalidateDCache();
		} // namespace cache
	} // namespace di
} // namespace bsp
