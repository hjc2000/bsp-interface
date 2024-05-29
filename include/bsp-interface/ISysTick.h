#pragma once
#include<chrono>
#include<stdint.h>

namespace bsp
{
	/// <summary>
	///		arm 都有一个 systick，其他 CPU 可能也有。没有的话就不实现本接口
	///		或使用定时器外设来模拟。
	/// </summary>
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
