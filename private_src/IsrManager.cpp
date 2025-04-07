#include "IsrManager.h"
#include "bsp-interface/di/interrupt.h"
#include "bsp-interface/di/task.h"

namespace
{
	class Init
	{
	public:
		Init()
		{
			bsp::IsrManager::Instance();
		}
	};

	Init volatile _isr_manager_hjc_init{};

} // namespace

bsp::IIsrManager &bsp::IsrManager::Instance()
{
	static bsp::IsrManager o{};
	return o;
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
	bsp::di::task::TaskGuard g;
	bsp::di::interrupt::GlobalInterruptGuard global_interrupt_guard;
	_isr_map[irq] = handler;
}

void bsp::IsrManager::RemoveIsr(uint32_t irq) noexcept
{
	bsp::di::task::TaskGuard g;
	bsp::di::interrupt::GlobalInterruptGuard global_interrupt_guard;
	_isr_map.erase(irq);
}
