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
        virtual void Open(bsp::IDmaOptions const &options) = 0;
        virtual bool IsOpen() const = 0;
        virtual void Close() = 0;

        /// @brief 返回底层的句柄。
        /// @return
        virtual void *Handle() = 0;
    };
} // namespace bsp
