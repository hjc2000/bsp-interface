#pragma once
#include "base/peripheral/IDma.h"
#include <base/string/define.h>
#include <stdexcept>
#include <string>

namespace bsp
{
	namespace dma
	{
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
													  base::dma::PeripheralIncrement peripheral_increment,
													  base::dma::MemoryIncrement memory_increment,
													  base::dma::PeripheralDataAlignment const &peripheral_data_alignment,
													  base::dma::MemoryDataAlignment const &memory_data_alignment,
													  base::dma::Priority priority,
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
			virtual void OpenAsMemoryToPeripheralMode(void *parent,
													  base::dma::PeripheralIncrement peripheral_increment,
													  base::dma::MemoryIncrement memory_increment,
													  base::dma::PeripheralDataAlignment const &peripheral_data_alignment,
													  base::dma::MemoryDataAlignment const &memory_data_alignment,
													  base::dma::Priority priority,
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
			virtual void OpenAsMomoryToMemoryMode(void *parent,
												  base::dma::PeripheralIncrement peripheral_increment,
												  base::dma::MemoryIncrement memory_increment,
												  base::dma::PeripheralDataAlignment const &peripheral_data_alignment,
												  base::dma::MemoryDataAlignment const &memory_data_alignment,
												  base::dma::Priority priority,
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
