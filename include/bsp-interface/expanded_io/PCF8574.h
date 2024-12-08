#pragma once
#include <bsp-interface/gpio/IGpioPin.h>
#include <bsp-interface/iic/IIicHost.h>
#include <functional>

namespace bsp
{
    /// @brief 这是一个使用 IIC 接口控制的扩展 IO 芯片。
    class PCF8574
    {
    private:
        std::string _name;
        bsp::IGpioPin *_interrupt_pin = nullptr;
        bsp::IIicHost *_iic_host = nullptr;
        uint8_t _address = 0x40;

    public:
        /// @brief 构造函数。
        /// @param name 本扩展 IO 的名称。
        /// @param interrupt_pin PCF8574 具有中断功能，需要一个中断输入引脚。
        /// @param iic_host 本对象需要一个 IIC 主机接口来控制 PCF8574 芯片。
        /// @param address PCF8574 芯片有一个地址，操作时需要用地址来指定芯片，一个 IIC 总线上可以挂
        /// 多个 PCF8574 芯片。
        PCF8574(std::string const &name,
                bsp::IGpioPin *interrupt_pin,
                bsp::IIicHost *iic_host,
                uint8_t address);

        /// @brief 注册中断回调函数。
        /// @param func
        void RegisterInterruptCallback(std::function<void()> func);

        /// @brief 取消注册中断回调函数。
        void UnregisterInterruptCallback();

        /// @brief 读取一个字节。这是一个 8 位的 IO 扩展芯片，读取 1 个字节意味着读取
        /// 所有 IO 端子的电平。
        /// @return
        uint8_t ReadByte();

        /// @brief 写 1 个字节。这是 1 个 8 位的 IO 扩展芯片，写 1 个字节意味着设置所有
        /// IO 端子的电平。
        /// @param value
        void WriteByte(uint8_t value);

        /// @brief 读取一个位。即读取指定索引的 IO 端子的电平。
        /// @param index IO 端子的索引。
        /// @return
        bool ReadBit(int index);

        /// @brief 写 1 个位。即写指定索引的 IO 端子的电平。
        /// @param index IO 端子的索引。
        /// @param value IO 端子的电平。
        void WriteBit(int index, bool value);
    };
} // namespace bsp
