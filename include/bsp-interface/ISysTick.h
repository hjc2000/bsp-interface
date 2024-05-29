#pragma once
#include<chrono>
#include<stdint.h>

namespace bsp
{
	class ISysTick
	{
	public:
		virtual uint32_t Frequency() = 0;
		virtual uint32_t CurrentValue() = 0;
		virtual uint32_t ReloadValue() = 0;

		virtual void NopLoopDelayForTicks(uint32_t tick_count);
		virtual void NopLoopDelay(std::chrono::microseconds microseconds);
		virtual void NopLoopDelay(std::chrono::milliseconds milliseconds);
		virtual void NopLoopDelay(std::chrono::seconds seconds);
	};
}
