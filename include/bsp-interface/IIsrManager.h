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
		///		设置 irq 对应的中断回调处理函数。
		/// </summary>
		/// <param name="irq"></param>
		/// <param name="handler"></param>
		void AddHandler(uint32_t irq, std::function<void()> handler);

		/// <summary>
		///		删除指定的中断回调处理函数。
		/// </summary>
		/// <param name="irq"></param>
		void RemoveHandler(uint32_t irq);
	};
}