#pragma once
#include <string>

namespace bsp
{
	namespace dma
	{
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

			class PeripheralDataAlignment
			{
			private:
				int _value = 4;

			public:
				explicit PeripheralDataAlignment(int value)
				{
					_value = value;
				}

				bool Value() const
				{
					return _value;
				}
			};

			class MemoryDataAlignment
			{
			private:
				int _value = 4;

			public:
				explicit MemoryDataAlignment(int value)
				{
					_value = value;
				}

				bool Value() const
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
			virtual void OpenAsPeripheralToMemoryMode(void *parent,
													  bsp::dma::property::PeripheralIncrement const &peripheral_increment,
													  bsp::dma::property::MemoryIncrement const &memory_increment,
													  bsp::dma::property::PeripheralDataAlignment const &peripheral_data_alignment,
													  bsp::dma::property::MemoryDataAlignment const &memory_data_alignment,
													  bsp::dma::property::Priority priority,
													  std::string const &request) = 0;

			/// @brief 打开 DMA，模式为将数据从内存拷贝到外设。
			/// @param parent DMA 要被连接到的父设备的句柄。例如对于 HAL 库的 USART，就是 UART_HandleTypeDef。
			/// @param peripheral_increment
			/// @param memory_increment
			/// @param peripheral_data_alignment
			/// @param memory_data_alignment
			/// @param priority
			/// @param request
			virtual void OpenAsMemoryToPeripheralMode(void *parent,
													  bsp::dma::property::PeripheralIncrement const &peripheral_increment,
													  bsp::dma::property::MemoryIncrement const &memory_increment,
													  bsp::dma::property::PeripheralDataAlignment const &peripheral_data_alignment,
													  bsp::dma::property::MemoryDataAlignment const &memory_data_alignment,
													  bsp::dma::property::Priority priority,
													  std::string const &request) = 0;

			/// @brief 打开 DMA，模式为将数据从内存拷贝到内存。
			/// @param parent DMA 要被连接到的父设备的句柄。例如对于 HAL 库的 USART，就是 UART_HandleTypeDef。
			/// @param peripheral_increment
			/// @param memory_increment
			/// @param peripheral_data_alignment
			/// @param memory_data_alignment
			/// @param priority
			/// @param request
			virtual void OpenAsMomoryToMemoryMode(void *parent,
												  bsp::dma::property::PeripheralIncrement const &peripheral_increment,
												  bsp::dma::property::MemoryIncrement const &memory_increment,
												  bsp::dma::property::PeripheralDataAlignment const &peripheral_data_alignment,
												  bsp::dma::property::MemoryDataAlignment const &memory_data_alignment,
												  bsp::dma::property::Priority priority,
												  std::string const &request) = 0;

			virtual bool IsOpen() const = 0;
			virtual void Close() = 0;

			/// @brief 剩余的未传输的字节数。
			/// @note 将本次启动 DMA 所设置的目标传输字节数减去本属性，即可得到传输了多少个字节。
			/// @return
			virtual int RemainingUntransmittedBytes() = 0;
		};
	} // namespace dma
} // namespace bsp
