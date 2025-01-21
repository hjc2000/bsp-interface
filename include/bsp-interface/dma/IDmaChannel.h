#pragma once
#include <base/string/define.h>
#include <stdexcept>
#include <string>

namespace bsp
{
	namespace dma
	{
		/// @brief DMA 属性
		namespace property
		{
			/// @brief DMA 优先级
			enum class Priority
			{
				Low,
				Medium,
				High,
				VeryHigh,
			};

			/// @brief DMA 在读写外设地址空间时，是否自动递增地址。即每读取 1 个字节，
			/// 就将地址递增 1.
			class PeripheralIncrement
			{
			private:
				bool _value = false;

			public:
				explicit PeripheralIncrement(bool value)
				{
					_value = value;
				}

				bool Value() const
				{
					return _value;
				}
			};

			/// @brief DMA 在读写内存地址空间时是否自动递增地址。即每读取 1 个字节，
			/// 就将地址递增 1.
			class MemoryIncrement
			{
			private:
				bool _value = false;

			public:
				explicit MemoryIncrement(bool value)
				{
					_value = value;
				}

				bool Value() const
				{
					return _value;
				}
			};

			/// @brief DMA 读写外设时采用的数据对齐字节数。例如 1 字节对齐或 4 字节对齐。
			class PeripheralDataAlignment
			{
			private:
				int _value = 4;

			public:
				explicit PeripheralDataAlignment(int value)
				{
					_value = value;
				}

				int Value() const
				{
					return _value;
				}
			};

			/// @brief DMA 读写内存时采用的数据对齐字节数。例如 1 字节对齐或 4 字节对齐。
			class MemoryDataAlignment
			{
			private:
				int _value = 4;

			public:
				explicit MemoryDataAlignment(int value)
				{
					_value = value;
				}

				int Value() const
				{
					return _value;
				}
			};
		} // namespace property

		/// @brief DMA 通道
		class IDmaChannel
		{
		public:
			virtual std::string Name() const = 0;

			/// @brief 打开 DMA，模式为将数据从外设拷贝到内存。
			/// @param parent DMA 要被连接到的父设备的句柄。例如对于 HAL 库的 USART，就是 UART_HandleTypeDef。
			/// @param peripheral_increment
			/// @param memory_increment
			/// @param peripheral_data_alignment
			/// @param memory_data_alignment
			/// @param priority
			/// @param request
			virtual void OpenAsPeripheralToMemoryMode(
				void *parent,
				bsp::dma::property::PeripheralIncrement const &peripheral_increment,
				bsp::dma::property::MemoryIncrement const &memory_increment,
				bsp::dma::property::PeripheralDataAlignment const &peripheral_data_alignment,
				bsp::dma::property::MemoryDataAlignment const &memory_data_alignment,
				bsp::dma::property::Priority priority,
				std::string const &request)
			{
				throw std::runtime_error{CODE_POS_STR + "不支持此模式"};
			}

			/// @brief 打开 DMA，模式为将数据从内存拷贝到外设。
			/// @param parent DMA 要被连接到的父设备的句柄。例如对于 HAL 库的 USART，就是 UART_HandleTypeDef。
			/// @param peripheral_increment
			/// @param memory_increment
			/// @param peripheral_data_alignment
			/// @param memory_data_alignment
			/// @param priority
			/// @param request
			virtual void OpenAsMemoryToPeripheralMode(
				void *parent,
				bsp::dma::property::PeripheralIncrement const &peripheral_increment,
				bsp::dma::property::MemoryIncrement const &memory_increment,
				bsp::dma::property::PeripheralDataAlignment const &peripheral_data_alignment,
				bsp::dma::property::MemoryDataAlignment const &memory_data_alignment,
				bsp::dma::property::Priority priority,
				std::string const &request)
			{
				throw std::runtime_error{CODE_POS_STR + "不支持此模式"};
			}

			/// @brief 打开 DMA，模式为将数据从内存拷贝到内存。
			/// @param parent DMA 要被连接到的父设备的句柄。例如对于 HAL 库的 USART，就是 UART_HandleTypeDef。
			/// @param peripheral_increment
			/// @param memory_increment
			/// @param peripheral_data_alignment
			/// @param memory_data_alignment
			/// @param priority
			/// @param request
			virtual void OpenAsMomoryToMemoryMode(
				void *parent,
				bsp::dma::property::PeripheralIncrement const &peripheral_increment,
				bsp::dma::property::MemoryIncrement const &memory_increment,
				bsp::dma::property::PeripheralDataAlignment const &peripheral_data_alignment,
				bsp::dma::property::MemoryDataAlignment const &memory_data_alignment,
				bsp::dma::property::Priority priority,
				std::string const &request)
			{
				throw std::runtime_error{CODE_POS_STR + "不支持此模式"};
			}

			virtual bool IsOpen() const = 0;
			virtual void Close() = 0;

			/// @brief 剩余的未传输的字节数。
			/// @note 将本次启动 DMA 所设置的目标传输字节数减去本属性，即可得到传输了多少个字节。
			/// @return
			virtual int RemainingUntransmittedBytes() = 0;
		};
	} // namespace dma
} // namespace bsp
