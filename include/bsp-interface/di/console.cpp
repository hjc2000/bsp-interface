#include "console.h"
#include <Console.h>

bsp::IConsole &DI_Console()
{
    return bsp::Console::Instance();
}
