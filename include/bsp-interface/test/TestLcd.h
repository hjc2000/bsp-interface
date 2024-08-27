#pragma once
#include <bsp-interface/di/delayer.h>
#include <bsp-interface/di/di.h>
#include <bsp-interface/di/lcd.h>
#include <bsp-interface/di/led.h>

#ifndef No_Build_Test
namespace bsp
{
    inline void TestLcd()
    {
        DI_GreenDigitalLed().TurnOn();
        DI_Lcd().DisplayOn();

        while (true)
        {
            DI_Delayer().Delay(std::chrono::seconds{1});
            for (uint32_t x = 0; x < DI_Lcd().Width(); x++)
            {
                for (uint32_t y = 0; y < DI_Lcd().Height(); y++)
                {
                    DI_Lcd().DrawPoint(x, y, 0x07E0);
                }
            }

            DI_Delayer().Delay(std::chrono::seconds{1});
            DI_Lcd().Clear(bsp::Color::Black);
            DI_RedDigitalLed().Toggle();
            DI_Delayer().Delay(std::chrono::seconds{1});
        }
    }
} // namespace bsp
#endif
