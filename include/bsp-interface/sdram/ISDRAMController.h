#pragma once
#include <base/stream/Span.h>
#include <bsp-interface/sdram/ISDRAMTiming.h>

namespace bsp
{
	namespace sdram
	{
		/// @brief SDRAM 控制器接口。
		/// @note 这个接口用来封装类似于 stm32 的 FMC 接口的 SDRAM 控制器。
		class ISDRAMController
		{
		public:
			/// @brief 打开 SDRAM 控制器。
			/// @param timing
			virtual void Open(bsp::sdram::ISDRAMTiming const &timing) = 0;
		};
	} // namespace sdram
} // namespace bsp
