#pragma once
#include "base/delegate/IEvent.h"
#include "base/net/Mac.h"
#include <vector>

namespace bsp
{
	/// @brief 以太网端口。
	class IEthernetPort
	{
	public:
		/// @brief 以太网控制器的名称。
		/// @return
		virtual std::string Name() const = 0;

		/// @brief 打开以太网端口。
		/// @param mac MAC 地址。
		virtual void Open(base::Mac const &mac) = 0;

		/// @brief 发送。
		/// @param spans
		virtual void Send(std::vector<base::ReadOnlySpan> const &spans) = 0;

		/// @brief 发送单个 span.
		/// @note 默认实现是基于 void Send(base::IEnumerable<base::ReadOnlySpan> const &spans).
		/// @param span
		virtual void Send(base::ReadOnlySpan const &span) = 0;

		/// @brief 收到以太网帧会触发此事件。
		/// @note 事件回调中会传入一个装有完整的以太网帧的 base::ReadOnlySpan.
		/// @return
		virtual base::IEvent<base::ReadOnlySpan> &ReceivingEhternetFrameEvent() = 0;

		/// @brief 连接事件。
		/// @note 链路层连接建立后会触发事件。
		/// @return
		virtual base::IEvent<> &ConnectionEvent() = 0;

		/// @brief 断开连接事件。
		/// @note 链路层连接断开后会触发事件。
		/// @return
		virtual base::IEvent<> &DisconnectionEvent() = 0;
	};
} // namespace bsp
