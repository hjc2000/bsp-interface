#include "YT8512CPhyDriver.h"
#include "base/peripheral/ethernet/parameter.h"
#include <base/container/Array.h>
#include <base/string/define.h>
#include <base/unit/Mbps.h>
#include <bsp-interface/di/console.h>

bsp::YT8512CPhyDriver::YT8512CPhyDriver(std::shared_ptr<bsp::IPhyController> const &phy_controller)
{
	if (phy_controller == nullptr)
	{
		throw std::invalid_argument{CODE_POS_STR + "不能是空指针。"};
	}

	_phy_controller = phy_controller;
}

bsp::IPhyController &bsp::YT8512CPhyDriver::PhyController()
{
	return *_phy_controller;
}

base::ethernet::DuplexMode bsp::YT8512CPhyDriver::DuplexMode()
{
	uint32_t register_value = ReadRegister(0x11);
	uint32_t const mask = 0b1 << 13;
	uint32_t duplex_register = (register_value & mask) >> 13;

	if (duplex_register)
	{
		bsp::di::Console().WriteLine("全双工");
		return base::ethernet::DuplexMode::FullDuplex;
	}

	bsp::di::Console().WriteLine("半双工");
	return base::ethernet::DuplexMode::HalfDuplex;
}

base::bps bsp::YT8512CPhyDriver::Speed()
{
	uint32_t register_value = ReadRegister(0x11);
	uint32_t const mask = 0b11 << 14;
	uint32_t duplex_register = (register_value & mask) >> 14;

	if (duplex_register == 0b00)
	{
		bsp::di::Console().WriteLine("连接速率：10 Mbps");
		return base::bps{base::Mbps{10}};
	}
	else if (duplex_register == 0b01)
	{
		bsp::di::Console().WriteLine("连接速率：100 Mbps");
		return base::bps{base::Mbps{100}};
	}
	else if (duplex_register == 0b01)
	{
		bsp::di::Console().WriteLine("连接速率：1000 Mbps");
		return base::bps{base::Mbps{1000}};
	}
	else
	{
		throw std::runtime_error{"读取连接速率寄存器时读取到保留值。"};
	}
}
