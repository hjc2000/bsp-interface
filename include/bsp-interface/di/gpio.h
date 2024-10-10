#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/gpio/IGpioPin.h>

/// @brief 创建一个 GPIO 引脚的配置对象。
/// @return
std::shared_ptr<bsp::IGpioPinOptions> DICreate_GpioPinOptions();

/// @brief GPIO 引脚集合
/// @return
base::IDictionary<std::string, bsp::IGpioPin *> const &DI_GpioPinCollection();
