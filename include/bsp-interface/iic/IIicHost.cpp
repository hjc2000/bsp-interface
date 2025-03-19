#include "IIicHost.h"

void bsp::IIicHost::SetSclCycleWhenGreater(std::chrono::microseconds value)
{
	if (value > SclCycle())
	{
		SetSclCycle(value);
	}
}

void bsp::IIicHost::SetWaitingForAckTimeoutCycleCountWhenGreater(int value)
{
	if (value > WaitingForAckTimeoutCycleCount())
	{
		SetWaitingForAckTimeoutCycleCount(value);
	}
}
