#include "interrupt.h"
#include <IsrManager.h>

bsp::IIsrManager &bsp::di::interrupt::IsrManager()
{
	return bsp::IsrManager::Instance();
}
