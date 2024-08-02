#pragma once
#include <bsp-interface/gpio/IGpioPin.h>

namespace bsp
{
	class IGpioPinManager
	{
	public:
		virtual bsp::IGpioPin &FindGpioPin(std::string pin_name) = 0;
	};
}
