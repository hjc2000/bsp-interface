#include "IClockSource.h"

#pragma region Open

void bsp::IClockSource::Open()
{
    throw std::runtime_error{"不支持此重载版本。"};
}

void bsp::IClockSource::Open(base::Hz const &crystal_frequency)
{
    throw std::runtime_error{"不支持此重载版本。"};
}

void bsp::IClockSource::Open(std::string const &input_channel_name)
{
    throw std::runtime_error{"不支持此重载版本。"};
}

void bsp::IClockSource::Open(IClockSource_TargetOutputFrequency const &target_output_frequency)
{
    throw std::runtime_error{"不支持此重载版本。"};
}

void bsp::IClockSource::Open(base::IDictionary<std::string, base::Hz> const &target_output_frequencies)
{
    throw std::runtime_error{"不支持此重载版本。"};
}

void bsp::IClockSource::Open(std::string const &input_channel_name,
                             base::IDictionary<std::string, base::Hz> const &target_output_frequencies)
{
    throw std::runtime_error{"不支持此重载版本。"};
}

void bsp::IClockSource::Open(std::string const &input_channel_name, base::Hz const &crystal_frequency, base::IDictionary<std::string, base::Hz> const &target_output_frequencies)
{
    throw std::runtime_error{"不支持此重载版本。"};
}

#pragma endregion

#pragma region SetAsBypass

void bsp::IClockSource::SetAsBypass(base::Hz external_clock_frequency)
{
    throw std::runtime_error{"不支持此重载版本。"};
}

void bsp::IClockSource::SetAsBypass(base::Hz external_clock_frequency, base::IDictionary<std::string, base::Hz> const &target_output_frequencies)
{
    throw std::runtime_error{"不支持此重载版本。"};
}

#pragma endregion
