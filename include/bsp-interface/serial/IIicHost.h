#pragma once
#include <stdint.h>
#include <string>

namespace bsp
{
    /// @brief IIC 主机接口。
    class IIicHost
    {
    public:
        /// @brief 此 IIC 接口的名称。
        /// @return
        virtual std::string Name() const = 0;

        /// @brief 打开 IIC 接口。
        virtual void Open() = 0;

        /// @brief 发送 IIC 启动信号。
        virtual void SendStartingSignal() = 0;

        /// @brief 发送 IIC 停止信号。
        virtual void SendStoppingSignal() = 0;

        /// @brief 发送一个字节。
        /// @param value
        virtual void SendByte(uint8_t value) = 0;

        /// @brief 读取 1 个字节。
        /// @param send_nack 读取完这个字节后是否发送 nack 信号终止读取。传入 true 则发送 nack 信号，
        /// 传入 false 则发送 ack 信号，表示希望继续读取。
        /// @return
        virtual uint8_t ReceiveByte(bool send_nack) = 0;
    };
} // namespace bsp
