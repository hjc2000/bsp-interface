#pragma once
#include <bsp-interface/serial/IIicHost.h>

namespace bsp
{
    /// @brief 这是一个使用 IIC 接口控制的扩展 IO 芯片。
    class PCF8574
    {
    private:
        std::string _name;
        bsp::IIicHost *_iic_host = nullptr;
        uint8_t _address = 0;

    public:
        /// @brief 构造函数。
        /// @param name 本扩展 IO 的名称。
        /// @param iic_host 本对象需要一个 IIC 主机接口来控制 PCF8574 芯片。
        /// @param address PCF8574 芯片有一个地址，操作时需要用地址来指定芯片，一个 IIC 总线上可以挂
        /// 多个 PCF8574 芯片。
        PCF8574(std::string const &name, bsp::IIicHost *iic_host, uint8_t address);
    };
} // namespace bsp
