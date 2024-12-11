#pragma once
#include <functional>
#include <stdint.h>

namespace bsp
{
    /// @brief 终端服务程序管理器。
    class IIsrManager
    {
    public:
        /// @brief 获取指定的中断向量对应的中断服务函数。
        /// @param irq
        /// @return
        virtual std::function<void()> &GetIsr(uint32_t irq) noexcept = 0;

        /// @brief 添加指定的中断向量的中断服务函数。
        /// @note 重复对同一个中断向量添加中断服务函数，将会覆盖之前添加的中断服务函数。
        ///
        /// @param irq
        /// @param handler
        virtual void AddIsr(uint32_t irq, std::function<void()> handler) noexcept = 0;

        /// @brief 删除指定的中断向量的中断服务函数。
        /// @param irq
        virtual void RemoveIsr(uint32_t irq) noexcept = 0;
    };
} // namespace bsp
