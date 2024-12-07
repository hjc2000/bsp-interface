#pragma once
#include <chrono>
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

        /// @brief SCL 的周期。
        /// @return
        virtual std::chrono::microseconds SclCycle() const = 0;

        /// @brief 设置 SCL 的周期。
        /// @param value
        virtual void SetSclCycle(std::chrono::microseconds value) = 0;

        /// @brief 如果传入的值比现有的 SCL 周期更大，则设置 SCL 的周期，否则不设置。
        /// @param value
        void SetSclCycleWhenGreater(std::chrono::microseconds value);

        /// @brief 等待从机的 ACK 信号的超时周期数。单位： SCL 的周期。
        /// @return
        virtual int WaitingForAckTimeoutCycleCount() const = 0;

        /// @brief 设置等待从机的 ACK 信号的超时周期数。单位： SCL 的周期。
        /// @param value
        virtual void SetWaitingForAckTimeoutCycleCount(int value) = 0;

        /// @brief 设置等待从机的 ACK 信号的超时周期数。但是本方法只有在新的值比旧的值
        /// 更大时才会设置。
        /// 单位： SCL 的周期。
        /// @param value
        void SetWaitingForAckTimeoutCycleCountWhenGreater(int value);
    };
} // namespace bsp
