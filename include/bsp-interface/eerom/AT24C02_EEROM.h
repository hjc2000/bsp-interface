#pragma once
#include <base/stream/ReadOnlySpan.h>
#include <bsp-interface/eerom/IEEROM.h>
#include <bsp-interface/iic/IIicHost.h>
#include <stdint.h>

namespace bsp
{
    /// @brief AT24C02 EEROM 芯片驱动。
    /// @note 这是一个使用 IIC 接口的 EEROM 芯片。
    class AT24C02_EEROM :
        public bsp::IEEROM
    {
    private:
        bsp::IIicHost *_iic_host = nullptr;
        std::string _name;

    public:
        /// @brief 构造函数。
        /// @param name 本 EEROM 的名称。
        /// @param host 连接着本芯片的 IIC 主机接口对象。
        AT24C02_EEROM(std::string const &name, bsp::IIicHost *host);

        /// @brief EEROM 的名称。
        /// @return
        std::string Name() const override;

        /// @brief EEROM 的容量。单位：字节。
        /// @return
        int32_t Size() const override;

        /// @brief 读取 1 个字节的数据。
        /// @param addr 数据地址。
        /// @return 读取到的字节。
        uint8_t ReadByte(int32_t addr) override;

        /// @brief 写 1 个字节的数据。
        /// @param addr 数据地址。
        /// @param data 数据。
        void WriteByte(int32_t addr, uint8_t data) override;
    };
} // namespace bsp
