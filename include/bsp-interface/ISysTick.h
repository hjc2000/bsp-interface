#pragma once
#include<chrono>
#include<stdint.h>

namespace bsp
{
	class ISysTick
	{
	public:
		virtual uint32_t Frequency() = 0;

		virtual void NopLoopDelayForTicks(uint32_t tick_count) = 0;
		virtual void NopLoopDelay(std::chrono::microseconds microseconds) = 0;
		virtual void NopLoopDelay(std::chrono::milliseconds milliseconds) = 0;
		virtual void NopLoopDelay(std::chrono::seconds seconds) = 0;
	};
}
