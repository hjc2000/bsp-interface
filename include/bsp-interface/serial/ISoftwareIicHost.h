#pragma once
#include <stdint.h>
#include <string>

namespace bsp
{
    /// @brief SDA 方向枚举。
    enum class ISoftwareIicHost_SDADirection
    {
        Input,
        Output,
    };

    /// @brief 通过软件模拟的 IIC 总线主机接口。
    class ISoftwareIicHost
    {
    private:
        /// @brief 发送应答信号。
        void SendAcknowledgment();

        /// @brief 发送非应答信号。
        void SendNotAcknowledgment();

        /// @brief 等待应答信号。
        /// @return 成功等到应答信号返回 true，没有等到返回 false.
        bool WaitForAcknowledgment();

        /// @brief 发送一位数据。
        /// @param value
        void SendBit(bool value);

        /// @brief 接收一个位。
        /// @return
        bool ReceiveBit();

    public:
#pragma region 接口
        /// @brief 此 IIC 接口的名称。
        /// @return
        virtual std::string Name() const = 0;

        /// @brief 打开 IIC 接口。
        virtual void Open() = 0;

        /// @brief 写 SCL 引脚的值。
        /// @param value
        virtual void WriteSCL(bool value) = 0;

        /// @brief 更改 SDA 引脚的 IO 方向。
        /// @param value
        virtual void ChangeSDADirection(ISoftwareIicHost_SDADirection value) = 0;

        /// @brief 写 SDA 引脚的值。
        /// @param value
        virtual void WriteSDA(bool value) = 0;

        /// @brief 读 SDA 引脚的值。
        /// @return
        virtual bool ReadSDA() const = 0;
#pragma endregion

        /// @brief 发送 IIC 启动信号。
        void SendStartingSignal();

        /// @brief 发送 IIC 停止信号。
        void SendStoppingSignal();

        /// @brief 发送一个字节。
        /// @param value
        /// @return 发送出去后，成功等到应答信号返回 true，没有等到应答信号返回 false.
        bool SendByte(uint8_t value);

        /// @brief 读取 1 个字节。
        /// @param send_nack 读取完这个字节后是否发送 nack 信号终止读取。传入 true 则发送 nack 信号，
        /// 传入 false 则发送 ack 信号，表示希望继续读取。
        /// @return
        uint8_t ReceiveByte(bool send_nack);
    };
} // namespace bsp
