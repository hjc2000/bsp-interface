#include "IsrManager.h"
#include <base/Initializer.h>
#include <bsp-interface/di.h>

using namespace bsp;

static base::Initializer _initializer{
	[]()
	{
		bsp::IsrManager::Instance();
	}};

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
