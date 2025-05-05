#include "PCF8574.h"
#include "base/embedded/iic/IicHost.h"
#include "base/task/delay.h"
#include <bsp-interface/di/gpio.h>
#include <bsp-interface/di/interrupt.h>

bsp::PCF8574::PCF8574(std::string const &name,
					  bsp::IGpioPin *interrupt_pin,
					  std::shared_ptr<base::iic::IicHost> const &iic_host,
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
	base::iic::IicHostOperator op{*_iic_host};

	op.Initialize(base::Nanoseconds{std::chrono::microseconds{4}},
				  base::Nanoseconds{std::chrono::microseconds{4} * 20});

	op.SendStartingSignal();
	op.SendByte(_address_register | 0x01);
	uint8_t data = op.ReceiveByte(true);
	op.SendStoppingSignal();
	return data;
}

void bsp::PCF8574::WriteByte(int index, uint8_t value)
{
	base::iic::IicHostOperator op{*_iic_host};

	op.Initialize(base::Nanoseconds{std::chrono::microseconds{4}},
				  base::Nanoseconds{std::chrono::microseconds{4} * 20});

	op.SendStartingSignal();
	op.SendByte(_address_register | 0x00);
	op.SendByte(value);
	op.SendStoppingSignal();
	base::task::Delay(std::chrono::milliseconds{10});
}
