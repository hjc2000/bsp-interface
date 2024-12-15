#include "LAN8720A_EthernetPort.h"
#include <bsp-interface/di/console.h>
#include <bsp-interface/di/system_time.h>

bsp::Ethernet_DuplexMode bsp::LAN8720A_EthernetPort::DuplexMode()
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

base::Bps bsp::LAN8720A_EthernetPort::Speed()
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
