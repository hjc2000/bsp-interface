#pragma once
#include <bsp-interface/ethernet/IEthernetPort.h>

namespace bsp
{
	/// @brief 根据 IEEE 标准，实现部分 bsp::IEthernetPort 功能。这部分功能只要是遵循 IEEE
	/// 标准的 PHY 都一样。
	class StandardEthernetPort :
		public bsp::IEthernetPort
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

		/// @brief 重启网口。
		/// @note 会保留 MAC 地址等配置。
		/// @note 会重新进行自动协商的过程。断线重连后可以调用本方法，防止 MAC 控制器
		/// 所使用的速率、双工等配置与新插入的网线不符。
		virtual void Restart() = 0;

		/// @brief 硬件复位 PHY 芯片。
		virtual void ResetPHY() = 0;

		/// @brief 获取此网口的双工模式。
		/// @return
		virtual bsp::Ethernet_DuplexMode DuplexMode() = 0;

		/// @brief 获取此网口的速度。
		/// @return
		virtual base::Bps Speed() = 0;

		/// @brief 发送。
		/// @param spans
		virtual void Send(base::IEnumerable<base::ReadOnlySpan> const &spans) = 0;

		/// @brief 接收。
		/// @return
		virtual base::IEnumerable<base::ReadOnlySpan> const &Receive() = 0;

		/// @brief 软件复位 PHY.
		virtual void SoftwareResetPHY() override;

#pragma region 自动协商
		/// @brief 检查本网口是否支持自动协商。
		/// @return 支持则返回 true，不支持则返回 false.
		virtual bool SupportAutoNegotiation() override;

		/// @brief 使能自动协商。
		/// @note 会先判断 PHY 是否支持自动协商，不支持自动协商会抛出异常。
		/// @note 使能自动协商后会等待 PHY 自动协商完成。等待超时后会抛出异常。
		virtual void EnableAutoNegotiation() override;

		/// @brief 自动协商完成。
		/// @return
		virtual bool AutoNegotiationCompleted() override;
#pragma endregion

		virtual void EnablePowerDownMode() override;
		virtual void DisablePowerDownMode() override;

		virtual void EnableLoopbackMode() override;
		virtual void DisableLoopbackMode() override;

		/// @brief 网线当前处于链接状态。
		/// @return
		virtual bool IsLinked() override;
	};
} // namespace bsp
