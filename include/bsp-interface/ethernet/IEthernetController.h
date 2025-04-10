#pragma once
#include <base/container/iterator/IEnumerable.h>
#include <base/net/Mac.h>
#include <base/stream/Stream.h>
#include <base/unit/bps.h>
#include <base/unit/Mbps.h>
#include <bsp-interface/ethernet/EthernetDuplexMode.h>
#include <bsp-interface/ethernet/EthernetInterfaceType.h>
#include <string>

namespace bsp
{
	/// @brief 以太网控制器接口。
	/// @note 以太网控制器使用 MII（独立介质接口）或 RMII（精简独立介质接口）控制外部的 PHY 芯片。
	class IEthernetController
	{
	public:
		/// @brief 以太网控制器的名称。
		/// @return
		virtual std::string Name() const = 0;

		/// @brief 打开以太网控制器。
		/// @param interface_type 连接着 PHY 的接口类型。（使用的是 MII 还是 RMII）
		/// @param phy_address PHY 的地址。
		/// @param mac MAC 地址。
		virtual void Open(bsp::EthernetInterfaceType interface_type,
						  uint32_t phy_address,
						  base::Mac const &mac) = 0;

		/// @brief 获取本控制器绑定的 MAC 地址。
		/// @note 要打开本控制器后本属性才有效。
		/// @return
		virtual base::Mac Mac() const = 0;

		/// @brief 读 PHY 的寄存器
		/// @param register_index 寄存器索引。
		/// @return
		virtual uint32_t ReadPHYRegister(uint32_t register_index) = 0;

		/// @brief 写 PHY 的寄存器。
		/// @param register_index 寄存器索引。
		/// @param value
		virtual void WritePHYRegister(uint32_t register_index, uint32_t value) = 0;

		/// @brief 启动以太网。
		/// @param duplex_mode
		/// @param speed
		virtual void Start(bsp::EthernetDuplexMode duplex_mode,
						   base::bps const &speed) = 0;

		/// @brief 发送。
		/// @note 现代的单片机的以太网控制器使用多个 DMA 描述符来控制数据传输。每个 DMA
		/// 描述符控制一个缓冲区的传输。一个或多个 DMA 描述符传输的缓冲区组成一个以太网帧。
		/// 即一个以太网帧可以被多个 DMA 描述符分成多个缓冲区进行传输。但是一个 DMA 描述符
		/// 不能传输多个以太网帧。这里使用 base::IEnumerable<base::ReadOnlySpan> 就是
		/// 为了适应这种多个缓冲区组成一个以太网帧的模式。spans 中的所有 span 共同组成一个
		/// 完整的以太网帧。spans 中不能放置多个以太网帧的 span.
		/// @param spans
		virtual void Send(base::IEnumerable<base::ReadOnlySpan> const &spans) = 0;

		/// @brief 发送单个 span.
		/// @note 默认实现是基于 void Send(base::IEnumerable<base::ReadOnlySpan> const &spans).
		/// @param span
		virtual void Send(base::ReadOnlySpan const &span);

		/// @brief 接收。
		/// @note 因为接收后需要解析，而解析需要数据完整且连续，所以必须接收一整个完整的以太网帧，
		/// 放到一个 span 中。
		/// @return
		virtual base::ReadOnlySpan Receive() = 0;
	};
} // namespace bsp
