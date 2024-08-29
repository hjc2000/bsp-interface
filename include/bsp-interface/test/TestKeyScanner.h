#pragma once
#include <bsp-interface/di/key.h>
#include <bsp-interface/di/led.h>

namespace bsp
{
    inline void TestKeyScanner()
    {
        while (true)
        {
            DI_KeyScanner().ScanKeys();
            if (DI_KeyScanner().HasKeyDownEvent("key0"))
            {
                DI_RedDigitalLed().Toggle();
            }

            if (DI_KeyScanner().HasKeyDownEvent("key1"))
            {
                DI_GreenDigitalLed().Toggle();
            }
        }
    }

} // namespace bsp
