#include "IicHostBase.h"

void bsp::IicHostBase::SetSclCycleWhenGreater(std::chrono::microseconds value)
{
	if (value > SclCycle())
	{
		SetSclCycle(value);
	}
}

void bsp::IicHostBase::SetWaitingForAckTimeoutCycleCountWhenGreater(int value)
{
	if (value > WaitingForAckTimeoutCycleCount())
	{
		SetWaitingForAckTimeoutCycleCount(value);
	}
}
