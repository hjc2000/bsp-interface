#pragma once
#include <bsp-interface/di/delayer.h>
#include <bsp-interface/di/di.h>
#include <bsp-interface/di/independent-watch-dog.h>
#include <bsp-interface/di/key.h>
#include <bsp-interface/di/led.h>

#ifndef No_Build_Test
namespace bsp
{
    inline void TestIndependentWatchDog()
    {
        DI_Delayer().Delay(std::chrono::milliseconds{500});
        DI_RedDigitalLed().TurnOn();
        DI_IndependentWatchDog().SetWatchDogTimeoutDuration(std::chrono::milliseconds(1000));

        while (true)
        {
            DI_KeyScanner().ScanKeys();
            if (DI_KeyScanner().HasKeyDownEvent("key0"))
            {
                DI_IndependentWatchDog().Feed();
            }
        }
    }

} // namespace bsp
#endif
