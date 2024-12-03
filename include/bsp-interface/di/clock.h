#pragma once
#include <base/container/IDictionary.h>
#include <base/unit/Hz.h>
#include <bsp-interface/clock/IClockSource.h>
#include <string>

/// @brief 时钟源集合。
/// @return
base::IDictionary<std::string, bsp::IClockSource *> const &DI_ClockSourceCollection();

/// @brief 查询指定的时钟信号的频率。
/// @param clock_signal_name
/// @return
base::Hz DI_GetClockSignalFrequency(std::string const &clock_signal_name);
