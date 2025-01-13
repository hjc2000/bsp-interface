#include "IsrManager.h"
#include <bsp-interface/di/interrupt.h>
#include <bsp-interface/di/task.h>
#include <bsp-interface/TaskSingletonGetter.h>

bsp::IIsrManager &bsp::IsrManager::Instance()
{
	class Getter :
		public bsp::TaskSingletonGetter<bsp::IsrManager>
	{
	public:
		std::unique_ptr<bsp::IsrManager> Create() override
		{
			return std::unique_ptr<bsp::IsrManager>{new bsp::IsrManager{}};
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
	bsp::TaskGuard g;
	bsp::GlobalInterruptGuard global_interrupt_guard;
	_isr_map[irq] = handler;
}

void bsp::IsrManager::RemoveIsr(uint32_t irq) noexcept
{
	bsp::TaskGuard g;
	bsp::GlobalInterruptGuard global_interrupt_guard;
	_isr_map.erase(irq);
}
