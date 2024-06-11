#pragma once
#include<functional>
#include<map>
#include<stdint.h>

namespace bsp
{
	/// <summary>
	///		管理定时器中断处理函数的回调。
	/// </summary>
	class ITimerInterruptManager
	{
	public:
		#pragma region 接口
		virtual std::map<uint32_t, std::function<void()>> &HandleMap() = 0;

		/// <summary>
		///		禁用 timer_id 指定的定时器的中断。
		/// </summary>
		/// <param name="timer_id"></param>
		virtual void DisableTimerInterrupt(uint32_t timer_id) = 0;

		/// <summary>
		///		启用 timer_id 指定的定时器的中断。
		/// </summary>
		/// <param name="timer_id"></param>
		virtual void EnableTimerInterrupt(uint32_t timer_id) = 0;
		#pragma endregion

		/// <summary>
		///		根据定时器 ID 获取定时器的中断处理函数。
		///		* 一般在中断向量触发的函数中进行调用。特殊情况可能手动调用来模拟出中断发生的情况。
		/// </summary>
		/// <param name="timer_id"></param>
		/// <returns></returns>
		std::function<void()> &GetTimerIrqHandler(uint32_t timer_id);

		/// <summary>
		///		通过定时器 ID 设置指定定时器的中断回调函数。
		///		* 本函数内部会调用 DisableTimerInterrupt 函数禁用定时器中断，并且不会启用中断，
		///		  需要在调用本函数后手动启用。
		/// </summary>
		/// <param name="timer_id"></param>
		/// <param name="handler"></param>
		void SetTimerIrqHandler(uint32_t timer_id, std::function<void()> handler);
	};
}