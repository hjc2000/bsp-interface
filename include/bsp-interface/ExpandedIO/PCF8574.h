#pragma once
#include <bsp-interface/ExpandedIO/IExpandedIoPort.h>
#include <bsp-interface/gpio/IGpioPin.h>
#include <bsp-interface/iic/IIicHost.h>
#include <functional>

namespace bsp
{
    /// @brief 这是一个使用 IIC 接口控制的扩展 IO 芯片。
    /// @note 每个引脚内部是一个开关管，所谓的写 1 就是将开关管关断，写 0 就是将开关管打开。
    /// 所以引脚外部需要使用上拉的方式进行接线。例如接 LED 时，需要将阴极连接到本芯片的引脚，
    /// 阳极连接着电源。
    /// @note 引脚电平发生变化后，会导致 PCF8574 的 INT 引脚变成低电平。这可以用来触发单片机
    /// 的外部中断。INT 引脚变成低电平后，必须对 PCF8574 进行一次写入或读取操作才能将 INT 恢复
    /// 成高电平。
    /// @note 因为写入操作也有恢复 PCF8574 的 INT 为高电平的功能，所以可以推测写入操作不会导致
    /// PCF8574 做出反应，进而触发 INT. 这点与单片机的 GPIO 不同。很多单片机的 GPIO 如果在输出
    /// 模式下又开启中断功能，自己写自己的引脚也会触发中断。
    class PCF8574 :
        public bsp::IExpandedIoPort
    {
    private:
        std::string _name;
        bsp::IGpioPin *_interrupt_pin = nullptr;
        bsp::IIicHost *_iic_host = nullptr;

        /// @brief 地址寄存器。高 4 位固定为 0b0100，低 4 位中的高 3 位是地址，最低位用来表示
        /// 读操作还是写操作。最低位为 1 表示读操作，最低位为 0 表示写操作。
        uint8_t _address_register = 0b01000000;

    public:
        /// @brief 构造函数。
        /// @param name 本扩展 IO 的名称。
        /// @param interrupt_pin PCF8574 具有中断功能，需要一个中断输入引脚。
        /// @param iic_host 本对象需要一个 IIC 主机接口来控制 PCF8574 芯片。
        /// @param address PCF8574 芯片有一个地址，操作时需要用地址来指定芯片，一个 IIC 总线上可以挂
        /// 多个 PCF8574 芯片。允许的地址范围为 [0, 7]，因为芯片上总共有 3 个引脚，用来接低电平或高电平
        /// 表示地址。
        PCF8574(std::string const &name,
                bsp::IGpioPin *interrupt_pin,
                bsp::IIicHost *iic_host,
                uint8_t address);

        std::string Name() const override;

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
