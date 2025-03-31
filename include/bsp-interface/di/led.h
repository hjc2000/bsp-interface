#pragma once
#include "base/peripheral/IDigitalLed.h"
#include <base/container/IDictionary.h>
#include <string>

namespace bsp
{
	namespace di
	{
		namespace led
		{
			/// @brief 数字 LED 灯集合。
			/// @return
			base::IDictionary<std::string, base::IDigitalLed *> const &DigitalLedCollection();

			base::IDigitalLed &RedDigitalLed();
			base::IDigitalLed &GreenDigitalLed();
			base::IDigitalLed &BlueDigitalLed();

		} // namespace led
	} // namespace di
} // namespace bsp
