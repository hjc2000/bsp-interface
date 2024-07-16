#pragma once
#include <bsp-interface/IDelayer.h>
#include <chrono>
#include <stdint.h>

namespace bsp
{
	/// @brief arm 都有一个 SysTick ，其他 CPU 可能也有。没有的话就不实现本接口
	/// 或使用定时器外设来模拟。
	class ISysTick
		: public bsp::IDelayer
	{
	public:
		virtual uint32_t Frequency() = 0;
		virtual uint32_t CurrentValue() = 0;
		virtual uint32_t ReloadValue() = 0;

		/// @brief 循环中检测 CurrentValue 的值来判断是否超时，从而进行延时。
		/// @param tick_count 要延时多少个 SysTick 的计数值。
		virtual void DelayForTicks(uint32_t tick_count);
		void Delay(std::chrono::microseconds microseconds) override;
		void Delay(std::chrono::milliseconds milliseconds) override;
		void Delay(std::chrono::seconds seconds) override;
	};
}
