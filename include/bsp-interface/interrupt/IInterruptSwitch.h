#pragma once
#include <stdint.h>

namespace bsp
{
    /// @brief 中断开关
    class IInterruptSwitch
    {
    public:
        virtual ~IInterruptSwitch() = default;

        /// @brief 禁用 irq 指定的中断。
        /// @param irq
        virtual void DisableInterrupt(uint32_t irq) noexcept = 0;

        /// @brief 启用 irq 指定的中断。
        /// @param irq
        virtual void EnableInterrupt(uint32_t irq) noexcept = 0;

        /// @brief 使能指定 irq 的中断。
        /// @param irq 中断号。
        /// @param priority 优先级。
        virtual void EnableInterrupt(uint32_t irq, uint32_t priority) noexcept = 0;

        /// @brief 禁止全局中断
        virtual void DisableGlobalInterrupt() noexcept = 0;

        /// @brief 启用全局中断
        virtual void EnableGlobalInterrupt() noexcept = 0;
    };
} // namespace bsp
