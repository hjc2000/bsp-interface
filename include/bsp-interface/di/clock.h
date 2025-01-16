#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/clock/IClockSignal.h>
#include <bsp-interface/clock/IClockSource.h>
#include <string>

namespace bsp
{
	namespace di
	{
		namespace clock
		{
			/// @brief 时钟源集合。
			/// @return
			base::IDictionary<std::string, bsp::IClockSource *> const &ClockSourceCollection();

			/// @brief 时钟信号集合。
			/// @return
			base::IDictionary<std::string, bsp::IClockSignal *> const &ClockSignalCollection();
		} // namespace clock
	} // namespace di
} // namespace bsp
