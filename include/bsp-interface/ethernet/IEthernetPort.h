#pragma once
#include <bsp-interface/ethernet/IEthernetController.h>

namespace bsp
{
	/// @brief 以太网端口。
	/// @note 端口就是以太网控制器 + PHY 芯片。
	/// @note 鉴于 PHY 芯片各品牌，各型号都不一样，各个 PHY 芯片都要定义一个类，继承本接口，
	/// 基于 bsp::IEthernetController 对象来实现以太网端口的功能。
	class IEthernetPort
	{
	public:
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

		/// @brief 硬件复位 PHY 芯片。
		virtual void ResetPHY() = 0;

		/// @brief 软件复位 PHY.
		virtual void SoftwareResetPHY() = 0;

		/// @brief 使能自动协商。
		virtual void EnableAutoNegotiation() = 0;

		virtual void EnablePowerDownMode() = 0;
		virtual void DisablePowerDownMode() = 0;

		virtual void EnableLoopbackMode() = 0;
		virtual void DisableLoopbackMode() = 0;

		/// @brief 获取此网口的双工模式。
		/// @return
		virtual bsp::Ethernet_DuplexMode DuplexMode() = 0;

		/// @brief 获取此网口的速度。
		/// @return
		virtual base::Bps Speed() = 0;
	};
} // namespace bsp
