#include "di.h"
#include <base/Initializer.h>

bsp::IsrManager &DI_IsrManager()
{
    return bsp::IsrManager::Instance();
}
