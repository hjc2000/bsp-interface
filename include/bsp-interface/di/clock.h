#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/clock/IClockSignal.h>
#include <string>

namespace bsp
{
	namespace di
	{
		namespace clock
		{
			/// @brief 时钟信号集合。
			/// @return
			base::IDictionary<std::string, bsp::IClockSignal *> const &ClockSignalCollection();
		} // namespace clock
	} // namespace di
} // namespace bsp
