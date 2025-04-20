#pragma once
#include "base/peripheral/ethernet/EthernetController.h"
#include "base/peripheral/ethernet/parameter.h"
#include <bsp-interface/ethernet/phy/IPhyDriver.h>

namespace bsp
{
	class YT8512CPhyDriver :
		public bsp::IPhyDriver
	{
	private:
		base::ethernet::EthernetController _ethernet_controller;

	public:
		YT8512CPhyDriver(base::ethernet::EthernetController const &controller);

		virtual base::ethernet::EthernetController &EthernetController() override;

		/// @brief 获取此网口的双工模式。
		/// @return
		virtual base::ethernet::DuplexMode DuplexMode() override;

		/// @brief 获取此网口的速度。
		/// @return
		virtual base::bps Speed() override;
	};
} // namespace bsp
