#include "IEthernetPort.h"
#include <bsp-interface/di/console.h>
#include <bsp-interface/di/delayer.h>

#pragma region 自动协商

void bsp::IEthernetPort::SoftwareResetPHY()
{
	/* BCR 的 bit15 用来软件复位。写入 1 立刻进行软件复位。
	 * 复位过程中，bit15 会保持为 1，复位完成后自动清 0. 所以可以通过检查自动清 0
	 * 来判断复位结束。
	 */
	uint32_t const mask = 0b1 << 15;
	WritePHYRegister(0, mask);

	int delay_times = 0;
	while (true)
	{
		uint32_t bcr = ReadPHYRegister(0);
		uint32_t value = bcr & mask;
		if (!value)
		{
			// 自动请 0，复位完成。
			DI_Console().WriteError("软件复位完成。");
			return;
		}

		DI_Delayer().Delay(std::chrono::milliseconds{10});
		delay_times++;
		if (delay_times > 1000)
		{
			DI_Console().WriteError("软件复位超时。");
			throw std::runtime_error{"软件复位超时。"};
		}
	}
}

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
			DI_Console().WriteError("自动协商完成。");
			return;
		}

		DI_Delayer().Delay(std::chrono::milliseconds{10});
		delay_times++;

		// 根据 IEEE 的规定，自动协商不应该超过 500ms，这里放宽松一点。
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

#pragma endregion

void bsp::IEthernetPort::EnablePowerDownMode()
{
	uint32_t bcr = ReadPHYRegister(0);
	bcr |= 0x0800U;
	WritePHYRegister(0, bcr);
}

void bsp::IEthernetPort::DisablePowerDownMode()
{
	uint32_t bcr = ReadPHYRegister(0);
	bcr &= ~0x0800U;
	WritePHYRegister(0, bcr);
}

void bsp::IEthernetPort::EnableLoopbackMode()
{
	uint32_t register_value = ReadPHYRegister(0);
	register_value |= 0x4000U;
	WritePHYRegister(0, register_value);
}

void bsp::IEthernetPort::DisableLoopbackMode()
{
	uint32_t register_value = ReadPHYRegister(0);
	register_value &= ~0x4000U;
	WritePHYRegister(0, register_value);
}
