#include "IEthernetPort.h"
#include <bsp-interface/di/console.h>
#include <bsp-interface/di/delayer.h>

bool bsp::IEthernetPort::SupportAutoNegotiation()
{
	/* BSR bit3 指示是否支持自动协商。
	 *		0：不支持自动协商。
	 *		1：支持自动协商。
	 */
	uint32_t bcr = ReadPHYRegister(1);
	uint32_t mask = 0b1 << 3;
	uint32_t value = (bcr & mask) >> 3;
	return value;
}

void bsp::IEthernetPort::EnableAutoNegotiation()
{
	if (!SupportAutoNegotiation())
	{
		DI_Console().WriteError("本网口不支持自动协商。");
		throw std::runtime_error{"本网口不支持自动协商。"};
	}

	/* 要先检查 BSR 看是否支持自动协商，支持才开启。
	 * 开启后要检查 BSR 寄存器，等待直到自动协商完成或超时。
	 */
	uint32_t bcr = ReadPHYRegister(0);
	bcr |= 0x1000U;
	WritePHYRegister(0, bcr);

	int delay_times = 0;
	while (true)
	{
		if (AutoNegotiationCompleted())
		{
			return;
		}

		DI_Delayer().Delay(std::chrono::milliseconds{10});
		delay_times++;

		// 最多等待 1000 次，也就是 10000 毫秒，也就是 10 秒。
		if (delay_times > 1000)
		{
			DI_Console().WriteError("等待自动协商完成超时");
			throw std::runtime_error{"等待自动协商完成超时"};
		}
	}
}

bool bsp::IEthernetPort::AutoNegotiationCompleted()
{
	/* BSR bit5 指示自动协商是否完成。
	 *		0：自动协商未完成。
	 *		1：自动协商完成。
	 */
	uint32_t bcr = ReadPHYRegister(1);
	uint32_t mask = 0b1 << 5;
	uint32_t value = (bcr & mask) >> 5;
	return value;
}
