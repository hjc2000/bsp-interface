#include "W9825G6KH_6_Timing.h"
#include <base/string/define.h>
#include <stdexcept>

bsp::W9825G6KH_6_Timing::W9825G6KH_6_Timing(base::Nanoseconds const &t_clk)
{
	_t_clk = t_clk;
	if (_t_clk <= base::Nanoseconds{0})
	{
		throw std::invalid_argument{CODE_POS_STR + "t_clk 不能为 0."};
	}
}

base::Nanoseconds bsp::W9825G6KH_6_Timing::T_CLK() const
{
	return _t_clk;
}

base::Nanoseconds bsp::W9825G6KH_6_Timing::T_RSC() const
{
	return 2 * _t_clk;
}

base::Nanoseconds bsp::W9825G6KH_6_Timing::T_XSR() const
{
	return base::Nanoseconds{72};
}

base::Nanoseconds bsp::W9825G6KH_6_Timing::T_RAS() const
{
	return base::Nanoseconds{42};
}

base::Nanoseconds bsp::W9825G6KH_6_Timing::T_RC() const
{
	return base::Nanoseconds{60};
}

base::Nanoseconds bsp::W9825G6KH_6_Timing::T_WR() const
{
	return 2 * _t_clk;
}

base::Nanoseconds bsp::W9825G6KH_6_Timing::T_RP() const
{
	return base::Nanoseconds{15};
}

base::Nanoseconds bsp::W9825G6KH_6_Timing::T_RCD() const
{
	return base::Nanoseconds{15};
}

base::Nanoseconds bsp::W9825G6KH_6_Timing::T_REF() const
{
	return base::Nanoseconds{std::chrono::milliseconds{64}};
}

int64_t bsp::W9825G6KH_6_Timing::RowCount() const
{
	return 8192;
}
