#pragma once
#include <bsp-interface/ethernet/phy/IPhyDriver.h>
#include <memory>

namespace bsp
{
	class LAN8720APhyDriver :
		public bsp::IPhyDriver
	{
	private:
		std::shared_ptr<bsp::IPhyController> _phy_controller;

	public:
		LAN8720APhyDriver(std::shared_ptr<bsp::IPhyController> const &phy_controller);

		virtual bsp::IPhyController &PhyController() override;

		/// @brief 获取此网口的双工模式。
		/// @return
		virtual bsp::EthernetDuplexMode DuplexMode() override;

		/// @brief 获取此网口的速度。
		/// @return
		virtual base::bps Speed() override;
	};
} // namespace bsp
