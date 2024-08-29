#include "interrupt.h"

bsp::IsrManager &DI_IsrManager()
{
    return bsp::IsrManager::Instance();
}
