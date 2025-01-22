#include "W9825G6KH_6_Timing.h"
#include <base/string/define.h>
#include <stdexcept>

bsp::sdram::chip::W9825G6KH_6_Timing::W9825G6KH_6_Timing(base::MHz const &f_clk)
{
	_f_clk = f_clk;
	if (T_CLK() <= base::Nanoseconds{0})
	{
		throw std::invalid_argument{CODE_POS_STR + "t_clk 不能为 0."};
	}
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_RSC() const
{
	return 2 * T_CLK();
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_XSR() const
{
	return base::Nanoseconds{72};
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_RAS() const
{
	return base::Nanoseconds{42};
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_RC() const
{
	return base::Nanoseconds{60};
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_WR() const
{
	return 2 * T_CLK();
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_RP() const
{
	return base::Nanoseconds{15};
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_RCD() const
{
	return base::Nanoseconds{15};
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_REF() const
{
	return base::Nanoseconds{std::chrono::milliseconds{64}};
}

int64_t bsp::sdram::chip::W9825G6KH_6_Timing::RowCount() const
{
	return 8192;
}

int bsp::sdram::chip::W9825G6KH_6_Timing::CASLatency() const
{
	if (CLKFrequency() > base::MHz{133})
	{
		return 3;
	}

	// 为了保险，始终使用 3，不知道怎么回事，家里的开发板用 2 一跑就崩。
	return 3;
}
