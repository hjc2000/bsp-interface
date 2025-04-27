#include "ISoftwareIicHost.h"
#include "base/embedded/gpio/gpio_parameter.h"
#include "base/task/delay.h"

void bsp::ISoftwareIicHost::SendAcknowledgment()
{
	WriteSCL(false);
	ChangeSDADirection(base::gpio::Direction::Output);
	WriteSDA(false);
	base::task::Delay(SclCycle() / 2);
	WriteSCL(true);
	base::task::Delay(SclCycle() / 2);
	WriteSCL(false);
}

void bsp::ISoftwareIicHost::SendNotAcknowledgment()
{
	WriteSCL(false);
	ChangeSDADirection(base::gpio::Direction::Output);
	WriteSDA(true);
	base::task::Delay(SclCycle() / 2);
	WriteSCL(true);
	base::task::Delay(SclCycle() / 2);
	WriteSCL(false);
}

bool bsp::ISoftwareIicHost::WaitForAcknowledgment()
{
	ChangeSDADirection(base::gpio::Direction::Input);
	WriteSDA(true);
	base::task::Delay(SclCycle() / 2);
	WriteSCL(true);
	base::task::Delay(SclCycle() / 2);

	int retry_times = 0;
	while (ReadSDA())
	{
		retry_times++;
		base::task::Delay(SclCycle() / 2);
		if (retry_times > WaitingForAckTimeoutCycleCount())
		{
			SendStoppingSignal();
			return false;
		}
	}

	WriteSCL(false);
	return true;
}

void bsp::ISoftwareIicHost::SendBit(bool value)
{
	ChangeSDADirection(base::gpio::Direction::Output);
	WriteSCL(false);
	WriteSDA(value);
	base::task::Delay(SclCycle() / 2);
	WriteSCL(true);
	base::task::Delay(SclCycle() / 2);
	WriteSCL(false);
	base::task::Delay(SclCycle() / 2);
}

bool bsp::ISoftwareIicHost::ReceiveBit()
{
	ChangeSDADirection(base::gpio::Direction::Input);
	WriteSCL(false);
	base::task::Delay(SclCycle() / 2);
	WriteSCL(true);
	bool bit = ReadSDA();
	base::task::Delay(SclCycle() / 2);
	return bit;
}

void bsp::ISoftwareIicHost::SendStartingSignal()
{
	ChangeSDADirection(base::gpio::Direction::Output);
	WriteSDA(true);
	WriteSCL(true);
	base::task::Delay(SclCycle());
	WriteSDA(false);
	base::task::Delay(SclCycle());
	WriteSCL(false);
}

void bsp::ISoftwareIicHost::SendStoppingSignal()
{
	ChangeSDADirection(base::gpio::Direction::Output);
	WriteSCL(false);
	WriteSDA(false);
	base::task::Delay(SclCycle());
	WriteSCL(true);
	WriteSDA(true);
	base::task::Delay(SclCycle());
}

void bsp::ISoftwareIicHost::SendByte(uint8_t value)
{
	for (int i = 0; i < 8; i++)
	{
		// 取出最高位。IIC 是从最高位开始发送。
		bool bit = value & 0x80;
		SendBit(bit);

		// 将次高位变成最高位。
		value <<= 1;
	}

	bool ack = WaitForAcknowledgment();
	if (!ack)
	{
		throw std::runtime_error{"IIC 接口 " + Name() + " 发送数据时未收到从机的应答信号"};
	}
}

uint8_t bsp::ISoftwareIicHost::ReceiveByte(bool send_nack)
{
	uint8_t data = 0;
	for (int i = 0; i < 8; i++)
	{
		bool bit = ReceiveBit();
		data <<= 1;
		if (bit)
		{
			data |= 0x1;
		}
	}

	if (send_nack)
	{
		SendNotAcknowledgment();
	}
	else
	{
		SendAcknowledgment();
	}

	return data;
}
