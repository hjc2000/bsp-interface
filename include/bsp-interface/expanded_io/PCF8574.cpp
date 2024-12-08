#include "PCF8574.h"
#include <bsp-interface/di/delayer.h>
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

uint8_t bsp::PCF8574::ReadByte()
{
    _iic_host->SendStartingSignal();
    _iic_host->SendByte(_address | 0x01);
    uint8_t data = _iic_host->ReceiveByte(true);
    _iic_host->SendStoppingSignal();
    return data;
}

void bsp::PCF8574::WriteByte(uint8_t value)
{
    _iic_host->SendStartingSignal();
    _iic_host->SendByte(_address | 0x00);
    _iic_host->SendByte(value);
    _iic_host->SendStoppingSignal();
    DI_Delayer().Delay(std::chrono::milliseconds{10});
}

bool bsp::PCF8574::ReadBit(int index)
{
    if (index < 0 || index > 7)
    {
        throw std::out_of_range{"指定的 IO 端子的索引超出范围"};
    }

    uint8_t data = ReadByte();
    uint8_t mask = 0x1 << index;
    return data & mask;
}

void bsp::PCF8574::WriteBit(int index, bool value)
{
    if (index < 0 || index > 7)
    {
        throw std::out_of_range{"指定的 IO 端子的索引超出范围"};
    }

    uint8_t byte = ReadByte();
    uint8_t mask = 0x1 << index;
    if (value)
    {
        byte |= mask;
    }
    else
    {
        byte &= ~mask;
    }

    WriteByte(byte);
}
