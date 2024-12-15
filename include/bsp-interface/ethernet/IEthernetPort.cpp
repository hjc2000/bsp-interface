#include "IEthernetPort.h"

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
		throw std::runtime_error{"本网口不支持自动协商。"};
	}

	/* 要先检查 BSR 看是否支持自动协商，支持才开启。
	 * 开启后要检查 BSR 寄存器，等待直到自动协商完成或超时。
	 */
	uint32_t bcr = ReadPHYRegister(0);
	bcr |= 0x1000U;
	WritePHYRegister(0, bcr);
}
