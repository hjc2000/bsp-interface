#include "LAN8720APhyDriver.h"
#include <base/container/Array.h>
#include <base/unit/Mbps.h>
#include <bsp-interface/di/console.h>
#include <bsp-interface/di/delayer.h>

bsp::EthernetDuplexMode bsp::LAN8720APhyDriver::DuplexMode()
{
	uint32_t register_value = ReadRegister(0x1F);
	uint32_t const mask = 0b10000;
	if (register_value & mask)
	{
		DI_Console().WriteLine("全双工");
		return bsp::EthernetDuplexMode::FullDuplex;
	}

	DI_Console().WriteLine("半双工");
	return bsp::EthernetDuplexMode::HalfDuplex;
}

base::Bps bsp::LAN8720APhyDriver::Speed()
{
	uint32_t register_value = ReadRegister(0x1F);
	uint32_t const mask = 0b01000;
	if (register_value & mask)
	{
		DI_Console().WriteLine("连接速率：100 Mbps");
		return base::Mbps{100};
	}

	DI_Console().WriteLine("连接速率：10 Mbps");
	return base::Mbps{10};
}
