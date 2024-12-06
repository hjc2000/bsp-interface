#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/gpio/IGpioPin.h>

/// @brief GPIO 引脚集合
/// @return
base::IDictionary<std::string, bsp::IGpioPin *> const &DI_GpioPinCollection();
