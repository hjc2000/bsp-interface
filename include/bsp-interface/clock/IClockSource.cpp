#include "IClockSource.h"

void bsp::IClockSource::TurnOn()
{
    TurnOn(1, 1);
}

void bsp::IClockSource::SetAsBypass(base::Hz external_clock_frequency)
{
    SetAsBypass(external_clock_frequency,
                1,
                1);
}
