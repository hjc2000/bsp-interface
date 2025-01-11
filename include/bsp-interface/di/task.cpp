#include "task.h"
#include <bsp-interface/di/interrupt.h>

bsp::TaskAndGlobalInterruptGuard::TaskAndGlobalInterruptGuard()
{
	DI_TaskManager().SuspendAllTask();
	DI_DisableGlobalInterrupt();
}

bsp::TaskAndGlobalInterruptGuard::~TaskAndGlobalInterruptGuard()
{
	DI_TaskManager().ResumeAllTask();
	DI_EnableGlobalInterrupt();
}
