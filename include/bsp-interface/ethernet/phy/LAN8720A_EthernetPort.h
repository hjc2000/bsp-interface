#pragma once
#include <bsp-interface/ethernet/IEthernetPort.h>

namespace bsp
{
	/// @brief 为 LAN8720A PHY 芯片部分实现 bsp::IEthernetPort.
	/// @note 无法完整实现 bsp::IEthernetPort，因为有些东西是板级的，例如 LAN8720A
	/// 需要一个引脚去硬件复位，而连接哪个 GPIO 引脚，或者连接到哪个扩展 IO 端子上，这些
	/// 都是具体的电路板去实现的。这部分实现要交给板级开发。板级开发继承本类，继续实现
	/// bsp::IEthernetPort 接口。
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
