#pragma once
#include <base/task/IMutex.h>
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
		std::shared_ptr<base::IMutex> _lock = base::CreateIMutex();

		/// @brief 接收用的锁。
		/// @note 以太网是双工的，接收和发送不能使用同一个锁。
		std::shared_ptr<base::IMutex> _receiving_lock = base::CreateIMutex();

		/// @brief 发送用的锁。
		/// @note 以太网是双工的，接收和发送不能使用同一个锁。
		std::shared_ptr<base::IMutex> _sending_lock = base::CreateIMutex();

		bsp::IEthernetPort *_port = nullptr;

	public:
		MutexEthernetPort(bsp::IEthernetPort *port);

		/// @brief 以太网控制器的名称。
		/// @return
		std::string Name() const override;

		/// @brief 打开以太网端口。
		/// @param mac MAC 地址。
		void Open(base::Mac const &mac) override;

		/// @brief 发送。
		/// @param spans
		void Send(std::vector<base::ReadOnlySpan> const &spans) override;

		/// @brief 发送单个 span.
		/// @note 默认实现是基于 void Send(base::IEnumerable<base::ReadOnlySpan> const &spans).
		/// @param span
		void Send(base::ReadOnlySpan const &span) override;

		/// @brief 收到以太网帧会触发此事件。
		/// @note 事件回调中会传入一个装有完整的以太网帧的 base::ReadOnlySpan.
		/// @return
		virtual base::IEvent<base::ReadOnlySpan> &ReceivingEhternetFrameEvent() override;

		/// @brief 连接事件。
		/// @note 链路层连接建立后会触发事件。
		/// @return
		virtual base::IEvent<> &ConnectionEvent() override;

		/// @brief 断开连接事件。
		/// @note 链路层连接断开后会触发事件。
		/// @return
		virtual base::IEvent<> &DisconnectionEvent() override;
	};
} // namespace bsp
