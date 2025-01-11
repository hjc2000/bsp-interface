#include "task.h"
#include <bsp-interface/di/interrupt.h>

bsp::TaskAndGlobalInterruptGuard::TaskAndGlobalInterruptGuard()
{
	DI_SuspendAllTask();
	DI_DisableGlobalInterrupt();
}

bsp::TaskAndGlobalInterruptGuard::~TaskAndGlobalInterruptGuard()
{
	DI_ResumeAllTask();
	DI_EnableGlobalInterrupt();
}
