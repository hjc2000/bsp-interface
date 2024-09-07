#pragma once
#include <base/di/SingletonGetter.h>
#include <bsp-interface/interrupt/IInterruptSwitch.h>
#include <functional>
#include <map>
#include <stdint.h>

bsp::IInterruptSwitch &DI_InterruptSwitch();

namespace bsp
{
    /// @brief 中断服务函数管理器
    class IsrManager final
    {
    private:
        IsrManager() = default;

        std::map<uint32_t, std::function<void()>> _isr_map;

        std::function<void()> _empty_func = []()
        {
        };

    public:
        static IsrManager &Instance()
        {
            class Getter : public base::SingletonGetter<IsrManager>
            {
            public:
                std::unique_ptr<IsrManager> Create() override
                {
                    return std::unique_ptr<IsrManager>{new IsrManager{}};
                }

                void Lock() override
                {
                    DI_InterruptSwitch().DisableGlobalInterrupt();
                }

                void Unlock() override
                {
                    DI_InterruptSwitch().EnableGlobalInterrupt();
                }
            };

            Getter g;
            return g.Instance();
        }

        /// @brief 获取指定的中断向量对应的中断服务函数。
        /// @param irq
        /// @return
        std::function<void()> &GetIsr(uint32_t irq) noexcept;

        /// @brief 添加指定的中断向量的中断服务函数。
        /// @note 重复对同一个中断向量添加中断服务函数，将会覆盖之前添加的中断服务函数。
        ///
        /// @param irq
        /// @param handler
        void AddIsr(uint32_t irq, std::function<void()> handler) noexcept;

        /// @brief 删除指定的中断向量的中断服务函数。
        /// @param irq
        void RemoveIsr(uint32_t irq) noexcept;
    };
} // namespace bsp
