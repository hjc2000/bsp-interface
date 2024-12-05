#pragma once
#include <base/stream/ReadOnlySpan.h>
#include <bsp-interface/serial/IIicHost.h>
#include <stdint.h>

namespace bsp
{
    /// @brief AT24C02 EEROM 芯片驱动。
    /// @note 这是一个使用 IIC 接口的 EEROM 芯片。
    class AT24C02_EEROM
    {
    private:
        bsp::IIicHost *_iic_host = nullptr;

    public:
        /// @brief 构造函数。
        /// @param host 连接着本芯片的 IIC 主机接口对象。传进来的 IIicHost 不要自行
        /// 调用 Open 方法，本对象会负责打开。
        AT24C02_EEROM(bsp::IIicHost *host);

        /// @brief EEROM 的容量。单位：字节。
        /// @return
        int32_t Size() const;

        /// @brief 读取 1 个字节的数据。
        /// @param addr 数据地址。
        /// @return 读取到的字节。
        uint8_t ReadByte(int32_t addr);

        void Read(int32_t addr, base::Span const &span);
        void Read(int32_t addr, uint8_t *buffer, int32_t offset, int32_t count);

        /// @brief 写 1 个字节的数据。
        /// @param addr 数据地址。
        /// @param data 数据。
        void WriteByte(int32_t addr, uint8_t data);

        void Write(int32_t addr, base::ReadOnlySpan const &span);
        void Write(int32_t addr, uint8_t const *buffer, int32_t offset, int32_t count);
    };
} // namespace bsp
