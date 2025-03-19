#pragma once
#include "base/stream/Span.h"

namespace bsp
{
	namespace sdram
	{
		class ISDRAM
		{
		public:
			/// @brief 打开 SDRAM.
			/// @note 分为 2 步：
			/// 	@li 打开 SDRAM 控制器。
			/// 	@li 初始化 SDRAM 芯片。
			virtual void Open() = 0;

			/// @brief 此 SDRAM 的内存段。
			/// @return
			virtual base::Span Span() const = 0;
		};
	} // namespace sdram
} // namespace bsp
