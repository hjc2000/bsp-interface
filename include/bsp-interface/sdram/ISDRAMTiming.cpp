#include "ISDRAMTiming.h"

base::Nanoseconds bsp::ISDRAMTiming::T_AutoRefreshCommand() const
{
	return T_REF() / RowCount();
}

base::Json bsp::ISDRAMTiming::ToJson() const
{
	base::Json root{
		{"RowCount", RowCount()},
		{"T_CLK", T_CLK().ToString()},
		{"T_RSC", static_cast<base::Fraction>(T_RSC() / T_CLK()).ToString()},
		{"T_XSR", static_cast<base::Fraction>(T_XSR() / T_CLK()).ToString()},
		{"T_RAS", static_cast<base::Fraction>(T_RAS() / T_CLK()).ToString()},
		{"T_RC", static_cast<base::Fraction>(T_RC() / T_CLK()).ToString()},
		{"T_WR", static_cast<base::Fraction>(T_WR() / T_CLK()).ToString()},
		{"T_RP", static_cast<base::Fraction>(T_RP() / T_CLK()).ToString()},
		{"T_RCD", static_cast<base::Fraction>(T_RCD() / T_CLK()).ToString()},
		{"T_REF", static_cast<base::Fraction>(T_REF() / T_CLK()).ToString()},
		{"T_AutoRefreshCommand", static_cast<base::Fraction>(T_AutoRefreshCommand() / T_CLK()).ToString()},
	};

	return root;
}
