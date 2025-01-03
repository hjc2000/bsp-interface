#pragma once
#include <base/container/IDictionary.h>
#include <base/unit/Hz.h>
#include <bsp-interface/clock/IClockSignal.h>
#include <bsp-interface/clock/IClockSource.h>
#include <string>

/// @brief 时钟源集合。
/// @return
base::IDictionary<std::string, bsp::IClockSource *> const &DI_ClockSourceCollection();

/// @brief 时钟信号集合。
/// @return
base::IDictionary<std::string, bsp::IClockSignal *> const &DI_ClockSignalCollection();
