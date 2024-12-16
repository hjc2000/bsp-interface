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

		/// @brief 重启网口。
		/// @note 会保留 MAC 地址等配置。
		/// @note 会重新进行自动协商的过程。断线重连后可以调用本方法，防止 MAC 控制器
		/// 所使用的速率、双工等配置与新插入的网线不符。
		virtual void Restart() = 0;

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

		/// @brief 获取此网口的双工模式。
		/// @return
		virtual bsp::Ethernet_DuplexMode DuplexMode() = 0;

		/// @brief 获取此网口的速度。
		/// @return
		virtual base::Bps Speed() = 0;

		/// @brief 软件复位 PHY.
		void SoftwareResetPHY();

#pragma region 自动协商
		/// @brief 检查本网口是否支持自动协商。
		/// @return 支持则返回 true，不支持则返回 false.
		bool SupportAutoNegotiation();

		/// @brief 使能自动协商。
		/// @note 会先判断 PHY 是否支持自动协商，不支持自动协商会抛出异常。
		/// @note 使能自动协商后会等待 PHY 自动协商完成。等待超时后会抛出异常。
		void EnableAutoNegotiation();

		/// @brief 自动协商完成。
		/// @return
		bool AutoNegotiationCompleted();
#pragma endregion

		void EnablePowerDownMode();
		void DisablePowerDownMode();

		void EnableLoopbackMode();
		void DisableLoopbackMode();

		/// @brief 发送。
		/// @param spans
		virtual void Send(base::IEnumerable<base::ReadOnlySpan> const &spans) = 0;

		/// @brief 接收。
		/// @return
		virtual base::IEnumerable<base::ReadOnlySpan> const &Receive() = 0;
	};
} // namespace bsp
