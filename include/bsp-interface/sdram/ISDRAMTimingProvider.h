#pragma once
#include <bsp-interface/sdram/ISDRAMTiming.h>
#include <memory>

namespace bsp
{
	namespace sdram
	{
		class ISDRAMTimingProvider
		{
		public:
			/// @brief 允许的最大 CLK 频率。
			/// @return
			virtual base::MHz MaxClkFrequency() const = 0;

			/// @brief 获取指定 CLK 频率下的时序。
			/// @param clk_frequency
			/// @return
			virtual std::shared_ptr<bsp::sdram::ISDRAMTiming> GetTiming(base::MHz const &clk_frequency) const = 0;
		};
	} // namespace sdram
} // namespace bsp
