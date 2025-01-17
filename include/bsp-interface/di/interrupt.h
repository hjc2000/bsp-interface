#pragma once
#include <bsp-interface/interrupt/IExtiManager.h>
#include <bsp-interface/interrupt/IIsrManager.h>
#include <stdint.h>

namespace bsp
{
	namespace di
	{
		namespace interrupt
		{
			/// @brief 禁用 irq 指定的中断。
			/// @param irq
			void DisableInterrupt(uint32_t irq) noexcept;

			/// @brief 启用 irq 指定的中断。
			/// @param irq
			void EnableInterrupt(uint32_t irq) noexcept;

			/// @brief 使能指定 irq 的中断。
			/// @param irq 中断号。
			/// @param priority 优先级。
			void EnableInterrupt(uint32_t irq, uint32_t priority) noexcept;

			/// @brief 禁止全局中断
			void DisableGlobalInterrupt() noexcept;

			/// @brief 启用全局中断
			void EnableGlobalInterrupt() noexcept;

			/// @brief 全局中断是否被禁止了。
			/// @return
			bool GlobalInterruptIsDisabled() noexcept;

			/// @brief 构造时禁用全局中断，析构时使能全局中断。
			class GlobalInterruptGuard
			{
			public:
				GlobalInterruptGuard()
				{
					DisableGlobalInterrupt();
				}

				~GlobalInterruptGuard()
				{
					EnableGlobalInterrupt();
				}
			};

			/// @brief 外部中断管理器。
			/// @return
			bsp::IExtiManager &ExtiManager();

#pragma region 已经实现
			/// @brief 中断管理器。
			/// @note 此依赖本库已经提供了，不需要实现此函数了。
			/// @return
			bsp::IIsrManager &IsrManager();
#pragma endregion
		} // namespace interrupt
	} // namespace di
} // namespace bsp
