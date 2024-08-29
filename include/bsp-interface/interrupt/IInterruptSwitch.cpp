#include "IInterruptSwitch.h"
#include <base/Guard.h>

void bsp::IInterruptSwitch::DoGlobalCriticalWork(std::function<void()> func)
{
    DisableGlobalInterrupt();
    base::Guard g{
        [this]()
        {
            EnableGlobalInterrupt();
        }};

    if (func)
    {
        func();
    }
}
