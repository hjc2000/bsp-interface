#include "W9825G6KH_6_TimingProvider.h"
#include <W9825G6KH_6_Timing.h>

std::shared_ptr<bsp::sdram::ISDRAMTiming> bsp::sdram::chip::W9825G6KH_6_TimingProvider::GetTiming(base::MHz const &clk_frequency) const
{
	if (clk_frequency > MaxClkFrequency())
	{
		throw std::invalid_argument{"时钟频率超过最大值"};
	}

	return std::shared_ptr<bsp::sdram::ISDRAMTiming>{new bsp::sdram::chip::W9825G6KH_6_Timing{clk_frequency}};
}
