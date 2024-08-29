#include "IInterruptSwitch.h"
#include <base/Guard.h>

void bsp::IInterruptSwitch::DoGlobalCriticalWork(std::function<void()> func)
{
    DisableGlobalInterrupt();

    // 保证即使抛出异常也能恢复全局中断的开启
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
