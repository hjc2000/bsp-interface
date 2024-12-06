#include "PCF8574.h"
#include <bsp-interface/di/gpio.h>
#include <bsp-interface/di/interrupt.h>

bsp::PCF8574::PCF8574(std::string const &name,
                      bsp::IGpioPin *interrupt_pin,
                      bsp::IIicHost *iic_host,
                      uint8_t address)
{
    _name = name;
    _interrupt_pin = interrupt_pin;
    _iic_host = iic_host;
    _address = address;

    // 打开中断引脚
    _interrupt_pin->OpenAsInputMode(bsp::IGpioPinPullMode::PullUp,
                                    bsp::IGpioPinTriggerEdge::FallingEdge);
}

void bsp::PCF8574::RegisterInterruptCallback(std::function<void()> func)
{
    _interrupt_pin->RegisterInterruptCallback(func);
}

void bsp::PCF8574::UnregisterInterruptCallback()
{
    _interrupt_pin->UnregisterInterruptCallback();
}
