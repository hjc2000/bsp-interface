#include "console.h"

bsp::Console &DI_Console()
{
    return bsp::Console::Instance();
}
