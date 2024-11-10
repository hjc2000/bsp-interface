#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/clock/IClockSource.h>
#include <string>

/// @brief 时钟源集合。
/// @return
base::IDictionary<std::string, bsp::IClockSource *> const &DI_ClockSourceCollection();
