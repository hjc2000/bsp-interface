#pragma once
#include <bsp-interface/sdram/ISDRAM.h>
#include <bsp-interface/sdram/ISDRAMController.h>

namespace bsp
{
	namespace di
	{
		namespace sdram
		{
			/// @brief 获取 ISDRAM 单例。
			/// @return
			bsp::sdram::ISDRAMController &SDRAMController();

			bsp::sdram::ISDRAM &SDRAM();
		} // namespace sdram
	} // namespace di
} // namespace bsp
