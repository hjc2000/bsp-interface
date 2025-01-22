#pragma once
#include <bsp-interface/sdram/chip/W9825G6KH_6_Timing.h>
#include <bsp-interface/sdram/ISDRAMTimingProvider.h>

namespace bsp
{
	namespace sdram
	{
		class W9825G6KH_6_TimingProvider :
			public bsp::sdram::ISDRAMTimingProvider
		{
		public:
			/// @brief 获取指定 CLK 频率下的时序。
			/// @param clk_frequency
			/// @return
			virtual std::shared_ptr<bsp::sdram::ISDRAMTiming> GetTiming(base::MHz const &clk_frequency) const override
			{
				return std::shared_ptr<bsp::sdram::ISDRAMTiming>{new bsp::sdram::chip::W9825G6KH_6_Timing{clk_frequency}};
			}
		};
	} // namespace sdram
} // namespace bsp
