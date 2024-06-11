#pragma once
#include<stdint.h>

namespace bsp
{
	class IInterruptSwitch
	{
	public:
		/// <summary>
		///		禁用 irq 指定的定时器的中断。
		/// </summary>
		/// <param name="irq"></param>
		virtual void DisableInterrupt(uint32_t irq) noexcept = 0;

		/// <summary>
		///		启用 irq 指定的定时器的中断。
		/// </summary>
		/// <param name="irq"></param>
		virtual void EnableInterrupt(uint32_t irq) noexcept = 0;
	};
}