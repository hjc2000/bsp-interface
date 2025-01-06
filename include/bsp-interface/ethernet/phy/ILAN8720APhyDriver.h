#pragma once
#include <bsp-interface/ethernet/phy/IPhyDriver.h>

namespace bsp
{
	class ILAN8720APhyDriver :
		public bsp::IPhyDriver
	{
	public:
		virtual bsp::IPhyController &PhyController() = 0;

		/// @brief 获取此网口的双工模式。
		/// @return
		bsp::EthernetDuplexMode DuplexMode() override;

		/// @brief 获取此网口的速度。
		/// @return
		base::Bps Speed() override;
	};
} // namespace bsp
