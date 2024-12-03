#include "IClockSignal.h"
#include <stdexcept>

void bsp::IClockSignal::Open(bsp::IClockSignal_InputDivisionFactor const &input_division_factor)
{
    throw std::runtime_error{"不支持此 Open 重载版本"};
}

void bsp::IClockSignal::Open(bsp::IClockSignal_OutputDivisionFactor const &output_division_factor)
{
    throw std::runtime_error{"不支持此 Open 重载版本"};
}

void bsp::IClockSignal::Open(bsp::IClockSignal_OutputDivisionFactor const &output_division_factor,
                             IClockSignal_ClockSource const &clock_source)
{
    throw std::runtime_error{"不支持此 Open 重载版本"};
}

void bsp::IClockSignal::Open(bsp::IClockSignal_InputDivisionFactor const &input_division_factor,
                             bsp::IClockSignal_OutputDivisionFactor const &output_division_factor)
{
    throw std::runtime_error{"不支持此 Open 重载版本"};
}
