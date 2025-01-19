#pragma once
#include <base/stream/Stream.h>
#include <string>

namespace bsp
{
	/// @brief 参数、枚举
	namespace serial
	{
		namespace property
		{
			/// @brief 校验方式
			enum class Parity
			{
				/// @brief 不校验。
				None,

				/// @brief 偶校验。
				Even,

				/// @brief 奇校验。
				Odd,
			};

			/// @brief 停止位位数。
			enum class StopBits
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

			/// @brief 硬件流控。
			enum class HardwareFlowControl
			{
				None,
				RTS,
				CTS,
				RTS_CTS,
			};

			/// @brief 串口数据传输方向。
			enum class Direction
			{
				RX,
				TX,
				RX_TX,
			};

			/// @brief 波特率。
			class BaudRate
			{
			private:
				uint32_t _value = 0;

			public:
				explicit BaudRate(uint32_t value)
					: _value(value)
				{
				}

				uint32_t Value() const
				{
					return _value;
				}
			};

			/// @brief 数据位位数。
			class DataBits
			{
			private:
				uint8_t _value = 0;

			public:
				explicit DataBits(uint8_t value)
					: _value(value)
				{
				}

				uint8_t Value() const
				{
					return _value;
				}
			};
		} // namespace property

		/// @brief 串口接口。
		class ISerial :
			public base::Stream
		{
		public:
			virtual std::string Name() = 0;

			/// @brief 打开串口。
			/// @param direction 串口数据方向。可以选择只发、只收、收发。
			/// @param baud_rate 波特率。
			/// @param data_bits 数据位位数。
			/// @param parity 奇偶校验。
			/// @param stop_bits 停止位位数。
			/// @param hardware_flow_control 硬件流控。
			virtual void Open(bsp::serial::property::Direction direction,
							  bsp::serial::property::BaudRate const &baud_rate,
							  bsp::serial::property::DataBits const &data_bits,
							  bsp::serial::property::Parity parity,
							  bsp::serial::property::StopBits stop_bits,
							  bsp::serial::property::HardwareFlowControl hardware_flow_control) = 0;

			/// @brief 使用默认参数打开。
			void Open();

			/// @brief 使用指定的波特率打开。其他参数默认。
			/// @param baud_rate 波特率。
			void Open(bsp::serial::property::BaudRate const &baud_rate);

#pragma region 串口属性
			/// @brief 数据传输方向
			/// @return
			virtual bsp::serial::property::Direction Direction() = 0;

			/// @brief 波特率。
			/// @return
			virtual uint32_t BaudRate() const = 0;

			/// @brief 数据位的个数。
			/// @return
			virtual uint8_t DataBits() const = 0;

			/// @brief 校验位。
			/// @return
			virtual bsp::serial::property::Parity Parity() const = 0;

			/// @brief 停止位个数。
			/// @return
			virtual bsp::serial::property::StopBits StopBits() const = 0;

			/// @brief 硬件流控。
			/// @return
			virtual bsp::serial::property::HardwareFlowControl HardwareFlowControl() const = 0;

			/// @brief 计算 frame_count 个帧占用多少个波特。
			/// @param frame_count
			/// @return
			uint32_t FramesBaudCount(uint32_t frame_count) const;
#pragma endregion

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
	} // namespace serial
} // namespace bsp
