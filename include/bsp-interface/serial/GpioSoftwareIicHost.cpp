#include "GpioSoftwareIicHost.h"

bsp::GpioSoftwareIicHost::GpioSoftwareIicHost(std::string name,
                                              std::string scl_pin_name,
                                              std::string sda_pin_name)
{
    _name = name;
    _scl_pin_name = scl_pin_name;
    _sda_pin_name = sda_pin_name;

    // 查找引脚
    {
        _scl_pin = DI_GpioPinCollection().Get(_scl_pin_name);
        _sda_pin = DI_GpioPinCollection().Get(_sda_pin_name);
    }

    // 输入引脚选项
    {
        _input_pin_options = DICreate_GpioPinOptions();
        _input_pin_options->SetWorkMode(bsp::IGpioPinWorkMode::Gpio);
        _input_pin_options->SetDirection(bsp::IGpioPinDirection::Input);
        _input_pin_options->SetTriggerEdge(bsp::IGpioPinTriggerEdge::Disable);
        _input_pin_options->SetPullMode(bsp::IGpioPinPullMode::PullUp);
        _input_pin_options->SetSpeedLevel(3);
    }

    // 输出引脚选项
    {
        _output_pin_options = DICreate_GpioPinOptions();
        _output_pin_options->SetWorkMode(bsp::IGpioPinWorkMode::Gpio);
        _output_pin_options->SetDirection(bsp::IGpioPinDirection::Output);
        _output_pin_options->SetDriver(bsp::IGpioPinDriver::PushPull);
        _output_pin_options->SetPullMode(bsp::IGpioPinPullMode::PullUp);
        _output_pin_options->SetSpeedLevel(3);
    }

    // 打开引脚
    {
        _scl_pin->OpenAsOutputMode(bsp::IGpioPinPullMode::PullUp, bsp::IGpioPinDriver::PushPull);
        _sda_pin->OpenAsOutputMode(bsp::IGpioPinPullMode::PullUp, bsp::IGpioPinDriver::PushPull);
    }

    // 空闲状态输出高电平
    {
        _scl_pin->WritePin(true);
        _sda_pin->WritePin(true);
    }
}

std::string bsp::GpioSoftwareIicHost::Name() const
{
    return _name;
}

void bsp::GpioSoftwareIicHost::WriteSCL(bool value)
{
    _scl_pin->WritePin(value);
}

void bsp::GpioSoftwareIicHost::ChangeSDADirection(ISoftwareIicHost_SDADirection value)
{
    // 要先关闭才能重新以新的配置打开引脚。
    _sda_pin->Close();
    if (value == bsp::ISoftwareIicHost_SDADirection::Input)
    {
        _sda_pin->OpenAsInputMode(bsp::IGpioPinPullMode::PullUp, bsp::IGpioPinTriggerEdge::Disable);
    }
    else
    {
        _sda_pin->OpenAsOutputMode(bsp::IGpioPinPullMode::PullUp, bsp::IGpioPinDriver::PushPull);
    }
}

void bsp::GpioSoftwareIicHost::WriteSDA(bool value)
{
    _sda_pin->WritePin(value);
}

bool bsp::GpioSoftwareIicHost::ReadSDA() const
{
    return _sda_pin->ReadPin();
}
