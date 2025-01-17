#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/IDigitalLed.h>
#include <string>

namespace bsp
{
	namespace di
	{
		namespace led
		{
			/// @brief 数字 LED 灯集合。
			/// @return
			base::IDictionary<std::string, bsp::IDigitalLed *> const &DigitalLedCollection();

			bsp::IDigitalLed &RedDigitalLed();
			bsp::IDigitalLed &GreenDigitalLed();
			bsp::IDigitalLed &BlueDigitalLed();
		} // namespace led
	} // namespace di
} // namespace bsp
