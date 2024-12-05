#pragma once
#include <bsp-interface/di/gpio.h>
#include <bsp-interface/serial/ISoftwareIicHost.h>

namespace bsp
{
    class GpioSoftwareIicHost :
        public bsp::ISoftwareIicHost
    {
    private:
        std::string _name;
        std::string _scl_pin_name;
        std::string _sda_pin_name;

        std::shared_ptr<bsp::IGpioPinOptions> _input_pin_options;
        std::shared_ptr<bsp::IGpioPinOptions> _output_pin_options;
        bsp::IGpioPin *_scl_pin = nullptr;
        bsp::IGpioPin *_sda_pin = nullptr;

    public:
        GpioSoftwareIicHost(std::string name,
                            std::string scl_pin_name,
                            std::string sda_pin_name);

        /// @brief 此 IIC 接口的名称。
        /// @return
        virtual std::string Name() const override;

        /// @brief 打开 IIC 接口。
        virtual void Open() override;

        /// @brief 写 SCL 引脚的值。
        /// @param value
        virtual void WriteSCL(bool value) override;

        /// @brief 更改 SDA 引脚的 IO 方向。
        /// @param value
        virtual void ChangeSDADirection(ISoftwareIicHost_SDADirection value) override;

        /// @brief 写 SDA 引脚的值。
        /// @param value
        virtual void WriteSDA(bool value) override;

        /// @brief 读 SDA 引脚的值。
        /// @return
        virtual bool ReadSDA() const override;
    };
} // namespace bsp
