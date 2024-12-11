#include "interrupt.h"
#include <IsrManager.h>

void DI_DoGlobalCriticalWork(std::function<void()> func)
{
    DI_DisableGlobalInterrupt();

    // 保证即使抛出异常也能恢复全局中断的开启
    base::Guard g{
        []()
        {
            DI_EnableGlobalInterrupt();
        }};

    if (func)
    {
        func();
    }
}

bsp::IIsrManager &DI_IsrManager()
{
    return bsp::IsrManager::Instance();
}
