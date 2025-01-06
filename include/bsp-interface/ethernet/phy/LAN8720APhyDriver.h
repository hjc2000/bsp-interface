#pragma once
#include <bsp-interface/ethernet/phy/IPhyDriver.h>

namespace bsp
{
	class LAN8720APhyDriver :
		public bsp::IPhyDriver
	{
	private:
		bsp::IPhyController &_phy_controller;

	public:
		LAN8720APhyDriver(bsp::IPhyController &phy_controller)
			: _phy_controller(phy_controller)
		{
		}

		virtual bsp::IPhyController &PhyController() override
		{
			return _phy_controller;
		}

		/// @brief 获取此网口的双工模式。
		/// @return
		virtual bsp::EthernetDuplexMode DuplexMode() override;

		/// @brief 获取此网口的速度。
		/// @return
		virtual base::Bps Speed() override;
	};
} // namespace bsp
