#pragma once
#include <base/define.h>
#include <base/di/SingletonGetter.h>
#include <bsp-interface/interrupt/IIsrManager.h>
#include <map>

namespace bsp
{
    /// @brief 中断服务函数管理器
    class IsrManager :
        public bsp::IIsrManager
    {
    private:
        IsrManager() = default;

        std::map<uint32_t, std::function<void()>> _isr_map;

        std::function<void()> _empty_func = []()
        {
        };

    public:
        static_function IsrManager &Instance();

        /// @brief 获取指定的中断向量对应的中断服务函数。
        /// @param irq
        /// @return
        std::function<void()> &GetIsr(uint32_t irq) noexcept override;

        /// @brief 添加指定的中断向量的中断服务函数。
        /// @note 重复对同一个中断向量添加中断服务函数，将会覆盖之前添加的中断服务函数。
        ///
        /// @param irq
        /// @param handler
        void AddIsr(uint32_t irq, std::function<void()> handler) noexcept override;

        /// @brief 删除指定的中断向量的中断服务函数。
        /// @param irq
        void RemoveIsr(uint32_t irq) noexcept override;
    };
} // namespace bsp
