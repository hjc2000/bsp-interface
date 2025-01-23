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
	// 额外加一个 T_CLK() 采用保守的时序
	return 2 * T_CLK() + T_CLK();
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_XSR() const
{
	// 额外加一个 T_CLK() 采用保守的时序
	return base::Nanoseconds{72} + T_CLK();
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_RAS() const
{
	// 额外加一个 T_CLK() 采用保守的时序
	return base::Nanoseconds{42} + T_CLK();
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_RC() const
{
	// 额外加一个 T_CLK() 采用保守的时序
	return base::Nanoseconds{60} + T_CLK();
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_WR() const
{
	// 额外加一个 T_CLK() 采用保守的时序
	return 2 * T_CLK() + T_CLK();
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_RP() const
{
	// 额外加一个 T_CLK() 采用保守的时序
	return base::Nanoseconds{15} + T_CLK();
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_RCD() const
{
	// 额外加一个 T_CLK() 采用保守的时序
	return base::Nanoseconds{15} + T_CLK();
}

base::Nanoseconds bsp::sdram::chip::W9825G6KH_6_Timing::T_REF() const
{
	// 提前 10ms 刷新
	return base::Nanoseconds{std::chrono::milliseconds{64}} - base::Nanoseconds{std::chrono::milliseconds{10}};
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
