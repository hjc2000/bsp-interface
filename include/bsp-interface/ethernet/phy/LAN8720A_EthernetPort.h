#pragma once
#include <bsp-interface/ethernet/IEthernetPort.h>

namespace bsp
{
	class LAN8720A_EthernetPort :
		public bsp::IEthernetPort
	{
	public:
		/// @brief 自动协商。
		void EnableAutoNegotiation() override;

		void EnablePowerDownMode() override;
		void DisablePowerDownMode() override;

		void EnableLoopbackMode() override;
		void DisableLoopbackMode() override;
	};
} // namespace bsp
