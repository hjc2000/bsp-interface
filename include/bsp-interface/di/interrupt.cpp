#include "interrupt.h"
#include <IsrManager.h>

bsp::IIsrManager &DI_IsrManager()
{
	return bsp::IsrManager::Instance();
}
