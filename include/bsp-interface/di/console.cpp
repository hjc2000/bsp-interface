#include "console.h"
#include <SafeConsole.h>

bsp::IConsole &bsp::di::Console()
{
	return bsp::SafeConsole::Instance();
}
