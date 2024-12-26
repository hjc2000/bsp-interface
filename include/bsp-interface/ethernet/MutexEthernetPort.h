#pragma once
#include <bsp-interface/di/task.h>
#include <bsp-interface/ethernet/IEthernetPort.h>

namespace bsp
{
	/// @brief 对 bsp::IEthernetPort 的互斥量包装器。
	class MutexEthernetPort :
		public bsp::IEthernetPort
	{
	private:
		/// @brief 控制用的锁。
		/// @note 控制与收发无关，所以要使用另外的一个锁。
		std::shared_ptr<bsp::IMutex> _lock = DICreate_Mutex();

		/// @brief 接收用的锁。
		/// @note 以太网是双工的，接收和发送不能使用同一个锁。
		std::shared_ptr<bsp::IMutex> _receiving_lock = DICreate_Mutex();

		/// @brief 发送用的锁。
		/// @note 以太网是双工的，接收和发送不能使用同一个锁。
		std::shared_ptr<bsp::IMutex> _sending_lock = DICreate_Mutex();

		bsp::IEthernetPort *_port = nullptr;

	public:
		MutexEthernetPort(bsp::IEthernetPort *port);

		/// @brief 以太网控制器的名称。
		/// @return
		std::string Name() const override;

		/// @brief 打开以太网端口。
		/// @param mac MAC 地址。
		void Open(base::Mac const &mac) override;

		/// @brief 读 PHY 的寄存器
		/// @param register_index 寄存器索引。
		/// @return
		uint32_t ReadPHYRegister(uint32_t register_index) override;

		/// @brief 写 PHY 的寄存器。
		/// @param register_index 寄存器索引。
		/// @param value
		void WritePHYRegister(uint32_t register_index, uint32_t value) override;

		/// @brief 重启网口。
		/// @note 会保留 MAC 地址等配置。
		/// @note 会重新进行自动协商的过程。断线重连后可以调用本方法，防止 MAC 控制器
		/// 所使用的速率、双工等配置与新插入的网线不符。
		void Restart() override;

		/// @brief 硬件复位 PHY 芯片。
		void ResetPHY() override;

		/// @brief 获取此网口的双工模式。
		/// @return
		bsp::Ethernet_DuplexMode DuplexMode() override;

		/// @brief 获取此网口的速度。
		/// @return
		base::Bps Speed() override;

		/// @brief 发送。
		/// @param spans
		void Send(base::IEnumerable<base::ReadOnlySpan> const &spans) override;

		/// @brief 接收。
		/// @note 因为接收后需要解析，而解析需要数据完整且连续，所以必须接收一整个完整的以太网帧，
		/// 放到一个 span 中。
		/// @return
		base::ReadOnlySpan Receive() override;

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
