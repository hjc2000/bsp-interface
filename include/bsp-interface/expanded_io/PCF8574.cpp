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

    /* 虽然 IIC 设备类不能调用 IIicHost 的 Open 方法，但是还是需要一些途径来改变 IIicHost
     * 的时钟频率、等待超时周期数。因为每个 IIC 设备类都有自己的响应速度上限。
     */
    _iic_host->SetSclCycleWhenGreater(std::chrono::microseconds{4});
    _iic_host->SetWaitingForAckTimeoutCycleCountWhenGreater(10);

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
