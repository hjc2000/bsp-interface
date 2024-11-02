#include "IsrManager.h"
#include <bsp-interface/di/interrupt.h>

using namespace bsp;

IsrManager &bsp::IsrManager::Instance()
{
    class Getter :
        public base::SingletonGetter<IsrManager>
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

std::function<void()> &bsp::IsrManager::GetIsr(uint32_t irq) noexcept
{
    auto it = _isr_map.find(irq);
    if (it != _isr_map.end())
    {
        std::function<void()> &func = it->second;
        return func;
    }

    return _empty_func;
}

void bsp::IsrManager::AddIsr(uint32_t irq, std::function<void()> handler) noexcept
{
    DI_InterruptSwitch().DisableGlobalInterrupt();
    _isr_map[irq] = handler;
    DI_InterruptSwitch().EnableGlobalInterrupt();
}

void bsp::IsrManager::RemoveIsr(uint32_t irq) noexcept
{
    DI_InterruptSwitch().DisableGlobalInterrupt();
    _isr_map.erase(irq);
    DI_InterruptSwitch().EnableGlobalInterrupt();
}
