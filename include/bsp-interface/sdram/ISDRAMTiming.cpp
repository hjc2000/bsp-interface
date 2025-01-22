#include "ISDRAMTiming.h"

base::Nanoseconds bsp::sdram::ISDRAMTiming::T_AutoRefreshCommand() const
{
	return T_REF() / RowCount();
}

base::Json bsp::sdram::ISDRAMTiming::ToJson() const
{
	base::Json root{
		{"RowCount", RowCount()},
		{"CLKFrequency", CLKFrequency().ToString()},
		{"T_CLK", T_CLK().ToString()},
		{"T_RSC_CLK_Count", T_RSC_CLK_Count()},
		{"T_XSR_CLK_Count", T_XSR_CLK_Count()},
		{"T_RAS_CLK_Count", T_RAS_CLK_Count()},
		{"T_RC_CLK_Count", T_RC_CLK_Count()},
		{"T_WR_CLK_Count", T_WR_CLK_Count()},
		{"T_RP_CLK_Count", T_RP_CLK_Count()},
		{"T_RCD_CLK_Count", T_RCD_CLK_Count()},
		{"T_REF_CLK_Count", T_REF_CLK_Count()},
		{"T_AutoRefreshCommand_CLK_Count", T_AutoRefreshCommand_CLK_Count()},
	};

	return root;
}
