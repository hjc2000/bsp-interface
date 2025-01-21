#include "ISDRAMTiming.h"

base::Nanoseconds bsp::sdram::ISDRAMTiming::T_AutoRefreshCommand() const
{
	return T_REF() / RowCount();
}

base::Json bsp::sdram::ISDRAMTiming::ToJson() const
{
	base::Json root{
		{"RowCount", RowCount()},
		{"T_CLK", T_CLK().ToString()},
		{"T_RSC", static_cast<base::Fraction>(T_RSC() / T_CLK()).Ceil()},
		{"T_XSR", static_cast<base::Fraction>(T_XSR() / T_CLK()).Ceil()},
		{"T_RAS", static_cast<base::Fraction>(T_RAS() / T_CLK()).Ceil()},
		{"T_RC", static_cast<base::Fraction>(T_RC() / T_CLK()).Ceil()},
		{"T_WR", static_cast<base::Fraction>(T_WR() / T_CLK()).Ceil()},
		{"T_RP", static_cast<base::Fraction>(T_RP() / T_CLK()).Ceil()},
		{"T_RCD", static_cast<base::Fraction>(T_RCD() / T_CLK()).Ceil()},
		{"T_REF", static_cast<base::Fraction>(T_REF() / T_CLK()).Ceil()},
		{"T_AutoRefreshCommand", static_cast<base::Fraction>(T_AutoRefreshCommand() / T_CLK()).Ceil()},
	};

	return root;
}
