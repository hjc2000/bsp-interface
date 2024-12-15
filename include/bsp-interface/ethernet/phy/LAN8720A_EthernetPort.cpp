#include "LAN8720A_EthernetPort.h"
#include <bsp-interface/di/system_time.h>

void bsp::LAN8720A_EthernetPort::SoftwareResetPHY()
{
	WritePHYRegister(0, 0x8000U);
	base::Seconds now = DI_SystemTime();
	while (true)
	{
		if (DI_SystemTime() - now > base::Seconds{std::chrono::milliseconds{1000}})
		{
			throw std::runtime_error{"软件复位 PHY 超时"};
		}

		uint32_t register_value = ReadPHYRegister(0);
		if (!(register_value & 0x8000U))
		{
			break;
		}
	}
}

void bsp::LAN8720A_EthernetPort::EnableAutoNegotiation()
{
	uint32_t bcr = ReadPHYRegister(0);
	bcr |= 0x1000U;
	WritePHYRegister(0, bcr);
}

void bsp::LAN8720A_EthernetPort::EnablePowerDownMode()
{
	uint32_t register_value = ReadPHYRegister(0);
	register_value |= 0x0800U;
	WritePHYRegister(0, register_value);
}

void bsp::LAN8720A_EthernetPort::DisablePowerDownMode()
{
	uint32_t register_value = ReadPHYRegister(0);
	register_value &= ~0x0800U;
	WritePHYRegister(0, register_value);
}

void bsp::LAN8720A_EthernetPort::EnableLoopbackMode()
{
	uint32_t register_value = ReadPHYRegister(0);
	register_value |= 0x4000U;
	WritePHYRegister(0, register_value);
}

void bsp::LAN8720A_EthernetPort::DisableLoopbackMode()
{
	uint32_t register_value = ReadPHYRegister(0);
	register_value &= ~0x4000U;
	WritePHYRegister(0, register_value);
}

bsp::Ethernet_DuplexMode bsp::LAN8720A_EthernetPort::DuplexMode()
{
	uint32_t register_value = ReadPHYRegister(0x1F);
	uint32_t const mask = 0b10000;
	if (register_value & mask)
	{
		return bsp::Ethernet_DuplexMode::FullDuplex;
	}

	return bsp::Ethernet_DuplexMode::HalfDuplex;
}

base::Bps bsp::LAN8720A_EthernetPort::Speed()
{
	uint32_t register_value = ReadPHYRegister(0x1F);
	uint32_t const mask = 0b01000;
	if (register_value & mask)
	{
		return base::Mbps{100};
	}

	return base::Mbps{10};
}
