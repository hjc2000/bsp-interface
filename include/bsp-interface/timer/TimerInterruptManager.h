#pragma once
#include<functional>
#include<map>
#include<stdint.h>

namespace bsp
{
	/// <summary>
	///		管理定时器中断处理函数的回调。
	/// </summary>
	class TimerInterruptManager
	{
	private:
		std::map<uint32_t, std::function<void()>> _handler_map;

	public:
		std::function<void()> &GetTimerIrqHandler(uint32_t timer_id);
		void SetTimerIrqHandler(uint32_t timer_id, std::function<void()> handler);
	};
}