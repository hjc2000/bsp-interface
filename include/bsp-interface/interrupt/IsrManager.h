#pragma once
#include <bsp-interface/interrupt/IInterruptSwitch.h>
#include <functional>
#include <map>
#include <stdint.h>

namespace bsp
{
	/// @brief 中断服务函数管理器
	class IsrManager
	{
	private:
		std::map<uint32_t, std::function<void()>> _isr_map;
		IInterruptSwitch &_interrupt_switch;

	public:
		IsrManager(IInterruptSwitch &interrupt_switch)
			: _interrupt_switch(interrupt_switch)
		{
		}

		/// @brief 获取指定的中断向量对应的中断服务函数。
		/// @warning 注意，返回的可能是 nullptr
		///
		/// @param irq
		/// @return
		std::function<void()> GetIsr(uint32_t irq);

		/// @brief 添加指定的中断向量的中断服务函数。
		/// @note 重复对同一个中断向量添加中断服务函数，将会覆盖之前添加的中断服务函数。
		///
		/// @param irq
		/// @param handler
		void AddIsr(uint32_t irq, std::function<void()> handler);

		/// @brief 删除指定的中断向量的中断服务函数。
		/// @param irq
		void RemoveIsr(uint32_t irq);
	};
}
