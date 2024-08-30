#pragma once
#include <bsp-interface/dma/IDmaOptions.h>
#include <string>

namespace bsp
{
    /// @brief DMA 通道
    class IDmaChannel
    {
    public:
        virtual std::string Name() const = 0;

        /// @brief 打开 DMA
        /// @param options DMA 初始化选项。
        /// @param parent DMA 要被连接到的父设备的句柄。例如对于 HAL 库的 USART，就是
        /// UART_HandleTypeDef。
        virtual void Open(bsp::IDmaOptions const &options, void *parent) = 0;

        virtual bool IsOpen() const = 0;
        virtual void Close() = 0;

        /// @brief 剩余的未传输的字节数。
        /// @note 将本次启动 DMA 所设置的目标传输字节数减去本属性，即可得到传输了多少个字节。
        /// @return
        virtual int RemainingUntransmittedBytes() = 0;
    };
} // namespace bsp
