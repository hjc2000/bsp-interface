#pragma once
#include <bsp-interface/expanded_io/IExpandedIoPort.h>
#include <bsp-interface/gpio/IGpioPin.h>
#include <bsp-interface/iic/IIicHost.h>
#include <functional>

namespace bsp
{
    /// @brief 这是一个使用 IIC 接口控制的扩展 IO 芯片。
    /// @note 每个引脚内部是一个开关管，所谓的写 1 就是将开关管关断，写 0 就是将开关管打开。
    /// 所以引脚外部需要使用上拉的方式进行接线。例如接 LED 时，需要将阴极连接到本芯片的引脚，
    /// 阳极连接着电源。
    class PCF8574 :
        public bsp::IExpandedIoPort
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
        void RegisterInterruptCallback(std::function<void()> func) override;

        /// @brief 取消注册中断回调函数。
        void UnregisterInterruptCallback() override;

        /// @brief 读取一个字节。这是一个 8 位的 IO 扩展芯片，读取 1 个字节意味着读取
        /// 所有 IO 端子的电平。
        /// @param index 索引。要读取第几个字节。
        /// @return
        uint8_t ReadByte(int index) override;

        /// @brief 写 1 个字节。这是 1 个 8 位的 IO 扩展芯片，写 1 个字节意味着设置所有
        /// IO 端子的电平。
        /// @param index 索引。要写入第几个字节。
        /// @param value
        void WriteByte(int index, uint8_t value) override;
    };
} // namespace bsp
