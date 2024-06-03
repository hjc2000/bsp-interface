#pragma once
#include<base/stream/Stream.h>

namespace bsp
{
	class ISerial :public base::Stream
	{
	public:
		/// <summary>
		///		波特率。
		/// </summary>
		/// <returns></returns>
		virtual uint32_t BaudRate() = 0;
		virtual void SetBaudRate(uint32_t value) = 0;

		/// <summary>
		///		数据位的个数。
		/// </summary>
		/// <returns></returns>
		virtual uint8_t DataBits() = 0;
		virtual void SetDataBits(uint8_t value) = 0;

		enum class ParityOption
		{
			None,
			Even,
			Odd,
		};

		/// <summary>
		///		校验位。
		/// </summary>
		/// <returns></returns>
		virtual bsp::ISerial::ParityOption Parity() = 0;
		virtual void SetParity(bsp::ISerial::ParityOption value) = 0;

		enum class StopBitsOption
		{
			None,
			ZeroPointFive, // 0.5
			One, // 1
			OnePointFive, // 1.5
			Tow, // 2
		};

		/// <summary>
		///		停止位个数。
		/// </summary>
		/// <returns></returns>
		virtual bsp::ISerial::StopBitsOption StopBits() = 0;
		virtual void SetStopBits(bsp::ISerial::StopBitsOption value) = 0;

		/// <summary>
		///		硬件流控。
		/// </summary>
		enum class HardwareFlowControlOption
		{
			None,
			RTS,
			CTS,
			RTS_CTS,
		};

		/// <summary>
		///		硬件流控。
		/// </summary>
		/// <returns></returns>
		virtual bsp::ISerial::HardwareFlowControlOption HardwareFlowControl() = 0;
		virtual void SetHardwareFlowControl(bsp::ISerial::HardwareFlowControlOption value) = 0;

		/// <summary>
		///		以指定的波特率启动串口。
		/// </summary>
		/// <param name="baud_rate"></param>
		virtual void Open() = 0;
	};
}
