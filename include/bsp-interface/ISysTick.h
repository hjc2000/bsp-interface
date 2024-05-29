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

		/// <summary>
		///		循环中检测 CurrentValue 的值来判断是否超时，从而进行延时。
		/// </summary>
		/// <param name="tick_count"></param>
		virtual void DelayForTicks(uint32_t tick_count);
		virtual void Delay(std::chrono::microseconds microseconds);
		virtual void Delay(std::chrono::milliseconds milliseconds);
		virtual void Delay(std::chrono::seconds seconds);
	};
}
