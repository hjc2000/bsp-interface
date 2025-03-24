#include "PCF8574.h"
#include "base/task/delay.h"
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

	if (address > 0b111)
	{
		throw std::out_of_range{"地址超出范围。允许的地址范围为 [0, 7]"};
	}

	_address_register = 0b01000000 | (address << 1);

	/* 虽然 IIC 设备类不能调用 IIicHost 的 Open 方法，但是还是需要一些途径来改变 IIicHost
	 * 的时钟频率、等待超时周期数。因为每个 IIC 设备类都有自己的响应速度上限。
	 */
	_iic_host->SetSclCycleWhenGreater(std::chrono::microseconds{4});
	_iic_host->SetWaitingForAckTimeoutCycleCountWhenGreater(10);

	// 打开中断引脚
	_interrupt_pin->OpenAsInputMode(bsp::IGpioPinPullMode::PullUp,
									bsp::IGpioPinTriggerEdge::FallingEdge);

	// 初始化后将所有引脚置为高电平。即让芯片内每个引脚的开关管关断。
	WriteByte(0, 0xff);
}

std::string bsp::PCF8574::Name() const
{
	return _name;
}

void bsp::PCF8574::RegisterInterruptCallback(std::function<void()> func)
{
	_interrupt_pin->RegisterInterruptCallback(func);
}

void bsp::PCF8574::UnregisterInterruptCallback()
{
	_interrupt_pin->UnregisterInterruptCallback();
}

uint8_t bsp::PCF8574::ReadByte(int index)
{
	_iic_host->SendStartingSignal();
	_iic_host->SendByte(_address_register | 0x01);
	uint8_t data = _iic_host->ReceiveByte(true);
	_iic_host->SendStoppingSignal();
	return data;
}

void bsp::PCF8574::WriteByte(int index, uint8_t value)
{
	_iic_host->SendStartingSignal();
	_iic_host->SendByte(_address_register | 0x00);
	_iic_host->SendByte(value);
	_iic_host->SendStoppingSignal();
	base::Delay(std::chrono::milliseconds{10});
}
