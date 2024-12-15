#pragma once
#include <bsp-interface/ethernet/IEthernetPort.h>

namespace bsp
{
	/// @brief 为 LAN8720A PHY 芯片部分实现 bsp::IEthernetPort.
	/// @note 无法完整实现 bsp::IEthernetPort，因为有些东西是板级的，例如 LAN8720A
	/// 需要一个引脚去硬件复位，而连接哪个 GPIO 引脚，或者连接到哪个扩展 IO 端子上，这些
	/// 都是具体的电路板去实现的。这部分实现要交给板级开发。板级开发继承本类，继续实现
	/// bsp::IEthernetPort 接口。
	class YT8512C_EthernetPort :
		public bsp::IEthernetPort
	{
	public:
#pragma region 未实现
		/// @brief 以太网控制器的名称。
		/// @return
		virtual std::string Name() const = 0;

		/// @brief 打开以太网端口。
		/// @param mac MAC 地址。
		virtual void Open(base::Mac const &mac) = 0;

		/// @brief 读 PHY 的寄存器
		/// @param register_index 寄存器索引。
		/// @return
		virtual uint32_t ReadPHYRegister(uint32_t register_index) = 0;

		/// @brief 写 PHY 的寄存器。
		/// @param register_index 寄存器索引。
		/// @param value
		virtual void WritePHYRegister(uint32_t register_index, uint32_t value) = 0;

		/// @brief 复位 PHY 芯片。
		virtual void ResetPHY() = 0;
#pragma endregion

		/// @brief 软件复位 PHY.
		void SoftwareResetPHY() override;

		/// @brief 自动协商。
		void EnableAutoNegotiation() override;

		void EnablePowerDownMode() override;
		void DisablePowerDownMode() override;

		void EnableLoopbackMode() override;
		void DisableLoopbackMode() override;

		/// @brief 获取此网口的双工模式。
		/// @return
		bsp::Ethernet_DuplexMode DuplexMode() override;

		/// @brief 获取此网口的速度。
		/// @return
		base::Bps Speed() override;
	};
} // namespace bsp
