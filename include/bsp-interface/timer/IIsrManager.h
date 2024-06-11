#pragma once
#include<functional>
#include<map>
#include<stdint.h>

namespace bsp
{
	/// <summary>
	///		中断服务函数管理器
	/// </summary>
	class IIsrManager
	{
	public:
		#pragma region 接口
		/// <summary>
		///		本类用户禁止通过本函数直接获取 map 来获得回调函数。必须使用 GetIrqHandlerFromIsr 函数。
		///		* 本函数是供本类内部使用，用户需要实现，实现后就不要去自己调用它。
		///		* 如果是 A 类，B 类都实现了本接口，B 类将 A 类作为字段，此时 B 类的 HandlerMap 函数实现可以
		///		  是转发 A 类的，这是合法的，除此以外，不要调用本函数。
		/// </summary>
		/// <returns></returns>
		virtual std::map<uint32_t, std::function<void()>> &HandlerMap() = 0;

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
		#pragma endregion

		/// <summary>
		///		在中断服务函数中根据定时器 ID 获取定时器的中断处理函数。
		///		* 禁止在非中断服务程序中调用，否则有可能会出错。
		/// </summary>
		/// <param name="irq"></param>
		/// <returns></returns>
		std::function<void()> const &GetIrqHandlerFromIsr(uint32_t irq);

		/// <summary>
		///		设置 irq 对应的中断回调函数。
		/// </summary>
		/// <param name="irq"></param>
		/// <param name="handler"></param>
		void SetIrqHandler(uint32_t irq, std::function<void()> handler);
	};
}