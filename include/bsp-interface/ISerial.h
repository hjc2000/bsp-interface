#pragma once
#include<base/stream/Stream.h>

namespace bsp
{
	class ISerial :
		public base::Stream
	{
	public:
		/// <summary>
		///		波特率。
		/// </summary>
		/// <returns></returns>
		virtual uint32_t BaudRate() const = 0;
		virtual void SetBaudRate(uint32_t value) = 0;

		/// <summary>
		///		数据位的个数。
		/// </summary>
		/// <returns></returns>
		virtual uint8_t DataBits() const = 0;
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
		virtual bsp::ISerial::ParityOption Parity() const = 0;
		virtual void SetParity(bsp::ISerial::ParityOption value) = 0;

		enum class StopBitsOption
		{
			ZeroPointFive, // 0.5
			One, // 1
			OnePointFive, // 1.5
			Tow, // 2
		};

		/// <summary>
		///		停止位个数。
		/// </summary>
		/// <returns></returns>
		virtual bsp::ISerial::StopBitsOption StopBits() const = 0;
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
		virtual bsp::ISerial::HardwareFlowControlOption HardwareFlowControl() const = 0;
		virtual void SetHardwareFlowControl(bsp::ISerial::HardwareFlowControlOption value) = 0;

		/// <summary>
		///		以指定的波特率启动串口。
		/// </summary>
		/// <param name="baud_rate"></param>
		virtual void Open() = 0;

		/// <summary>
		///		baud_count 个波特占用多少个 tick。
		/// 
		///		* 这里的 tick 只要是一个能提供时间基准的计数器就行，不一定是 SysTick，
		///		  也可以是定时器外设。
		/// </summary>
		/// <param name="baud_count"></param>
		/// <param name="tick_freq">tick 的频率</param>
		/// <returns></returns>
		uint64_t BaudTicks(uint32_t baud_count, uint32_t tick_freq) const;

		/// <summary>
		///		根据本对象的属性，计算出 frame_count 个串行帧占用多少个波特，
		///		然后计算占用多少个 tick。
		/// 
		///		* 这里的 tick 只要是一个能提供时间基准的计数器就行，不一定是 SysTick，
		///		  也可以是定时器外设。
		/// </summary>
		/// <param name="frame_count"></param>
		/// <param name="tick_freq"></param>
		/// <returns></returns>
		uint64_t FrameTicks(uint32_t frame_count, uint32_t tick_freq) const;

		#pragma region Stream
		bool CanRead() override;
		bool CanWrite() override;
		bool CanSeek() override;

		int64_t Length() override;
		void SetLength(int64_t value) override;

		void Flush() override;

		int64_t Position() override;
		void SetPosition(int64_t value) override;
		#pragma endregion

	};
}
