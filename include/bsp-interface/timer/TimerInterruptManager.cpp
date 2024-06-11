#include"TimerInterruptManager.h"

using namespace bsp;

std::function<void()> &bsp::TimerInterruptManager::GetTimerIrqHandler(uint32_t timer_id)
{
	return _handler_map[timer_id];
}

void bsp::TimerInterruptManager::SetTimerIrqHandler(uint32_t timer_id, std::function<void()> handler)
{
	_handler_map[timer_id] = handler;
}
