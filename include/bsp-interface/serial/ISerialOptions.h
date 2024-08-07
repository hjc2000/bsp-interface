#pragma once
#include <stdint.h>

namespace bsp
{
	/// @brief 用来设置 ISerial 的校验方式
	enum class ISerialParity
	{
		/// @brief 不校验。
		None,

		/// @brief 偶校验。
		Even,

		/// @brief 奇校验。
		Odd,
	};

	/// @brief 用来设置 ISerial 的停止位位数。
	enum class ISerialStopBits
	{
		/// @brief 0.5
		ZeroPointFive,

		/// @brief 1
		One,

		/// @brief 1.5
		OnePointFive,

		/// @brief 2
		Tow,
	};

	/// @brief 用来设置 ISerial 的硬件流控。
	enum class ISerialHardwareFlowControl
	{
		None,
		RTS,
		CTS,
		RTS_CTS,
	};

	/// @brief 串口数据传输方向。
	enum class ISerialDirection
	{
		RX,
		TX,
		RX_TX,
	};

	/// @brief 串口选项。
	class ISerialOptions
	{
	public:
		virtual ~ISerialOptions() = default;

		/// @brief 将本对象设置为默认配置。
		virtual void UseDefaultOptions() = 0;

		/// @brief 数据传输方向
		/// @return
		virtual bsp::ISerialDirection Direction() = 0;
		virtual void SetDirection(bsp::ISerialDirection value) = 0;

		/// @brief 波特率。
		/// @return
		virtual uint32_t BaudRate() const = 0;
		virtual void SetBaudRate(uint32_t value) = 0;

		/// @brief 数据位的个数。
		/// @return
		virtual uint8_t DataBits() const = 0;
		virtual void SetDataBits(uint8_t value) = 0;

		/// @brief 校验位。
		/// @return
		virtual bsp::ISerialParity Parity() const = 0;
		virtual void SetParity(bsp::ISerialParity value) = 0;

		/// @brief 停止位个数。
		/// @return
		virtual bsp::ISerialStopBits StopBits() const = 0;
		virtual void SetStopBits(bsp::ISerialStopBits value) = 0;

		/// @brief 硬件流控。
		/// @return
		virtual bsp::ISerialHardwareFlowControl HardwareFlowControl() const = 0;
		virtual void SetHardwareFlowControl(bsp::ISerialHardwareFlowControl value) = 0;

		/// @brief 计算 frame_count 个帧占用多少个波特。
		/// @param frame_count
		/// @return
		uint32_t CalculateFramesBaudCount(uint32_t frame_count);
	};
}
