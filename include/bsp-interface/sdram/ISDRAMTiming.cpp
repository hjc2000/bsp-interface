#include "ISDRAMTiming.h"

base::Nanoseconds bsp::ISDRAMTiming::T_AutoRefreshCommand() const
{
	return T_REF() / RowCount();
}

base::Json bsp::ISDRAMTiming::ToJson() const
{
	base::Json root{
		{"T_CLK", T_CLK().ToString()},
		{"T_RSC", T_RSC().ToString()},
		{"T_XSR", T_XSR().ToString()},
		{"T_RAS", T_RAS().ToString()},
		{"T_RC", T_RC().ToString()},
		{"T_WR", T_WR().ToString()},
		{"T_RP", T_RP().ToString()},
		{"T_RCD", T_RCD().ToString()},
		{"T_REF", T_REF().ToString()},
		{"RowCount", RowCount()},
		{"T_AutoRefreshCommand", T_AutoRefreshCommand().ToString()},
	};

	return root;
}
