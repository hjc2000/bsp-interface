#pragma once
#include <bsp-interface/ethernet/IEthernetPort.h>

namespace bsp
{
	/// @brief 为 YT8512C PHY 芯片部分实现 bsp::StandardEthernetPort.
	/// @note 无法完整实现 bsp::StandardEthernetPort，因为有些东西是板级的，例如 YT8512C
	/// 需要一个引脚去硬件复位，而连接哪个 GPIO 引脚，或者连接到哪个扩展 IO 端子上，这些
	/// 都是具体的电路板去实现的。这部分实现要交给板级开发。板级开发继承本类，继续实现
	/// bsp::StandardEthernetPort 接口。
	class YT8512C_EthernetPort :
		public bsp::IEthernetPort
	{
	public:
		/// @brief 获取此网口的双工模式。
		/// @return
		bsp::EthernetDuplexMode DuplexMode() override;

		/// @brief 获取此网口的速度。
		/// @return
		base::Bps Speed() override;
	};
} // namespace bsp
