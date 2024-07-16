#include "ISysTick.h"

using namespace bsp;

void ISysTick::DelayForTicks(uint32_t tick_count)
{
	uint32_t old_tick = CurrentValue();
	uint32_t total_tick = 0;
	while (true)
	{
		uint32_t now_tick = CurrentValue();
		if (old_tick == now_tick)
		{
			// CPU 太快了，导致再次进入循环后 SysTic 没来得及递增计数，所以 old_tick == now_tick
			continue;
		}

		uint32_t delta_tick = 0;
		if (old_tick > now_tick)
		{
			// 因为是减计数，所以此时没有发生环绕
			delta_tick = old_tick - now_tick;
		}
		else
		{
			// 发生了环绕
			// delta_tick = old_tick - (now_tick - reload)
			// delta_tick = old_tick - now_tick + reload
			delta_tick = old_tick - now_tick + ReloadValue();
		}

		total_tick += delta_tick;
		if (total_tick >= tick_count)
		{
			return;
		}

		old_tick = now_tick;
	}
}

void ISysTick::Delay(std::chrono::microseconds microseconds)
{
	uint32_t freq = Frequency();

	/*
	 * 时钟周期 T = 1 / freq
	 * 要延时的周期数
	 *	N = microseconds / 1e6 / T
	 *	N = microseconds / 1e6 * freq
	 * 因为 freq 较大，所以调整为
	 *	N = freq / 1e6 * microseconds
	 * 这样可避免溢出
	 */
	DelayForTicks(freq / (uint32_t)1e6 * microseconds.count());
}

void ISysTick::Delay(std::chrono::milliseconds milliseconds)
{
	Delay(std::chrono::microseconds{milliseconds});
}

void ISysTick::Delay(std::chrono::seconds seconds)
{
	Delay(std::chrono::milliseconds{seconds});
}
