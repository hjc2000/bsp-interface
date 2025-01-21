#pragma once
#include <bsp-interface/sdram/ISDRAM.h>

namespace bsp
{
	namespace di
	{
		namespace sdram
		{
			/// @brief 获取 ISDRAM 单例。
			/// @return
			bsp::ISDRAM &SDRAM();
		} // namespace sdram
	} // namespace di
} // namespace bsp
