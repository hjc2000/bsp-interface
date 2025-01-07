#pragma once
#include <base/delegate/Delegate.h>
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

		/// @brief 发送。
		/// @param spans
		virtual void Send(base::IEnumerable<base::ReadOnlySpan> const &spans) = 0;

		/// @brief 发送单个 span.
		/// @note 默认实现是基于 void Send(base::IEnumerable<base::ReadOnlySpan> const &spans).
		/// @param span
		virtual void Send(base::ReadOnlySpan const &span);

		/// @brief 收到以太网帧会触发此事件。
		/// @note 事件回调中会传入一个装有完整的以太网帧的 base::ReadOnlySpan.
		/// @return
		virtual base::IEvent<base::ReadOnlySpan> &ReceivintEhternetFrameEvent() = 0;

		/// @brief 网线当前处于链接状态。
		/// @return
		virtual bool IsLinked() = 0;
	};
} // namespace bsp
