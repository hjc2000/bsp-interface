#pragma once
#include <bsp-interface/ethernet/phy/IPhyDriver.h>
#include <memory>

namespace bsp
{
	class YT8512CPhyDriver :
		public bsp::IPhyDriver
	{
	private:
		std::shared_ptr<bsp::IPhyController> _phy_controller;

	public:
		YT8512CPhyDriver(std::shared_ptr<bsp::IPhyController> phy_controller);

		virtual bsp::IPhyController &PhyController() override;

		/// @brief 获取此网口的双工模式。
		/// @return
		virtual bsp::EthernetDuplexMode DuplexMode() override;

		/// @brief 获取此网口的速度。
		/// @return
		virtual base::Bps Speed() override;
	};
} // namespace bsp
