#include "YT8512C_EthernetPort.h"
#include <bsp-interface/di/console.h>
#include <bsp-interface/di/system_time.h>

void bsp::YT8512C_EthernetPort::SoftwareResetPHY()
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

void bsp::YT8512C_EthernetPort::EnableAutoNegotiation()
{
	uint32_t bcr = ReadPHYRegister(0);
	bcr |= 0x1000U;
	WritePHYRegister(0, bcr);
}

void bsp::YT8512C_EthernetPort::EnablePowerDownMode()
{
	uint32_t register_value = ReadPHYRegister(0);
	register_value |= 0x0800U;
	WritePHYRegister(0, register_value);
}

void bsp::YT8512C_EthernetPort::DisablePowerDownMode()
{
	uint32_t register_value = ReadPHYRegister(0);
	register_value &= ~0x0800U;
	WritePHYRegister(0, register_value);
}

void bsp::YT8512C_EthernetPort::EnableLoopbackMode()
{
	uint32_t register_value = ReadPHYRegister(0);
	register_value |= 0x4000U;
	WritePHYRegister(0, register_value);
}

void bsp::YT8512C_EthernetPort::DisableLoopbackMode()
{
	uint32_t register_value = ReadPHYRegister(0);
	register_value &= ~0x4000U;
	WritePHYRegister(0, register_value);
}

bsp::Ethernet_DuplexMode bsp::YT8512C_EthernetPort::DuplexMode()
{
	uint32_t register_value = ReadPHYRegister(0x1F);
	uint32_t const mask = 0b10000;
	if (register_value & mask)
	{
		DI_Console().WriteLine("全双工");
		return bsp::Ethernet_DuplexMode::FullDuplex;
	}

	DI_Console().WriteLine("半双工");
	return bsp::Ethernet_DuplexMode::HalfDuplex;
}

base::Bps bsp::YT8512C_EthernetPort::Speed()
{
	uint32_t register_value = ReadPHYRegister(0x1F);
	uint32_t const mask = 0b01000;
	if (register_value & mask)
	{
		DI_Console().WriteLine("连接速率：100 Mbps");
		return base::Mbps{100};
	}

	DI_Console().WriteLine("连接速率：10 Mbps");
	return base::Mbps{10};
}
