#include "IGpioPin.h"
#include <stdexcept>

void bsp::IGpioPin::OpenAsInputMode(bsp::IGpioPinPullMode pull_mode,
									bsp::IGpioPinTriggerEdge trigger_edge)
{
	throw std::runtime_error{"不支持此模式"};
}

void bsp::IGpioPin::OpenAsOutputMode(bsp::IGpioPinPullMode pull_mode, bsp::IGpioPinDriver driver)
{
	throw std::runtime_error{"不支持此模式"};
}

void bsp::IGpioPin::OpenAsAlternateFunctionMode(std::string function_name,
												bsp::IGpioPinPullMode pull_mode,
												bsp::IGpioPinDriver driver)
{
	throw std::runtime_error{"不支持此模式"};
}
