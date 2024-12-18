#include "console.h"
#include <SafeConsole.h>

bsp::IConsole &DI_Console()
{
	return bsp::SafeConsole::Instance();
}
