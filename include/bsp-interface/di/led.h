#pragma once
#include <base/container/ICollection.h>
#include <bsp-interface/IDigitalLed.h>
#include <string>

/// @brief 数字 LED 灯集合。
/// @return
base::IReadOnlyCollection<std::string, bsp::IDigitalLed *> &DI_DigitalLedCollection();

bsp::IDigitalLed &DI_RedDigitalLed();
bsp::IDigitalLed &DI_GreenDigitalLed();
bsp::IDigitalLed &DI_BlueDigitalLed();
