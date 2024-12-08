#pragma once
#include <bsp-interface/di/task.h>
#include <bsp-interface/iic/IIicHost.h>

namespace bsp
{
    /// @brief 包装 IIicHost 并转发操作。转发时会使用互斥量进行保护。
    /// @note IIC 主机接口是共享的，会挂载多个 IIC 设备，然后在多个地方操作这些设备，
    /// 并且很可能是在多线程中。这种情况下就需要使用本类包装裸的 IIicHost 对象，从而
    /// 使用互斥量进行保护。
    class MutexIicHost :
        public bsp::IIicHost
    {
    private:
        std::shared_ptr<bsp::IMutex> _lock = DICreate_Mutex();
        bsp::IIicHost *_host = nullptr;

    public:
        /// @brief 构造函数。
        /// @param host 未被互斥量保护的 IIicHost.
        MutexIicHost(bsp::IIicHost *host);

#pragma region IIicHost
        /// @brief 此 IIC 接口的名称。
        /// @return
        std::string Name() const override;

        /// @brief 发送 IIC 启动信号。
        void SendStartingSignal() override;

        /// @brief 发送 IIC 停止信号。
        void SendStoppingSignal() override;

        /// @brief 发送一个字节。
        /// @param value
        void SendByte(uint8_t value) override;

        /// @brief 读取 1 个字节。
        /// @param send_nack 读取完这个字节后是否发送 nack 信号终止读取。传入 true 则发送 nack 信号，
        /// 传入 false 则发送 ack 信号，表示希望继续读取。
        /// @return
        uint8_t ReceiveByte(bool send_nack) override;

        /// @brief SCL 的周期。
        /// @return
        std::chrono::microseconds SclCycle() const override;

        /// @brief 设置 SCL 的周期。
        /// @param value
        void SetSclCycle(std::chrono::microseconds value) override;

        /// @brief 等待从机的 ACK 信号的超时周期数。单位： SCL 的周期。
        /// @return
        int WaitingForAckTimeoutCycleCount() const override;

        /// @brief 设置等待从机的 ACK 信号的超时周期数。单位： SCL 的周期。
        /// @param value
        void SetWaitingForAckTimeoutCycleCount(int value) override;
#pragma endregion
    };
} // namespace bsp
