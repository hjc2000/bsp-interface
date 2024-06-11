#include"ITimerInterruptManager.h"

using namespace bsp;

std::function<void()> &bsp::ITimerInterruptManager::GetTimerIrqHandlerFromIsr(uint32_t timer_id)
{
	return HandleMap()[timer_id];
}

void bsp::ITimerInterruptManager::SetTimerIrqHandler(uint32_t timer_id, std::function<void()> handler)
{
	DisableTimerInterrupt(timer_id);
	HandleMap()[timer_id] = handler;
}
