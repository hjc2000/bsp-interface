#pragma once
#include <bsp-interface/sdram/chip/W9825G6KH_6_Timing.h>
#include <bsp-interface/sdram/ISDRAMTimingProvider.h>
#include <stdexcept>

namespace bsp
{
	namespace sdram
	{
		namespace chip
		{
			class W9825G6KH_6_TimingProvider :
				public bsp::sdram::ISDRAMTimingProvider
			{
			public:
				/// @brief 允许的最大 CLK 频率。
				/// @return
				virtual base::MHz MaxClkFrequency() const override
				{
					return base::MHz{166};
				}

				/// @brief 获取指定 CLK 频率下的时序。
				/// @param clk_frequency
				/// @return
				virtual std::shared_ptr<bsp::sdram::ISDRAMTiming> GetTiming(base::MHz const &clk_frequency) const override
				{
					if (clk_frequency > MaxClkFrequency())
					{
						throw std::invalid_argument{"时钟频率超过最大值"};
					}

					return std::shared_ptr<bsp::sdram::ISDRAMTiming>{new bsp::sdram::chip::W9825G6KH_6_Timing{clk_frequency}};
				}
			};
		} // namespace chip
	} // namespace sdram
} // namespace bsp
