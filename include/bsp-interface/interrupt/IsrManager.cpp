#include "IsrManager.h"
#include <bsp-interface/di.h>

using namespace bsp;

bsp::IsrManager::IsrManager()
	: _interrupt_switch(DI_InterruptSwitch())
{
}

std::function<void()> bsp::IsrManager::GetIsr(uint32_t irq)
{
	auto it = _isr_map.find(irq);
	if (it != _isr_map.end())
	{
		return it->second;
	}

	return nullptr;
}

void bsp::IsrManager::AddIsr(uint32_t irq, std::function<void()> handler)
{
	_interrupt_switch.DisableGlobalInterrupt();
	_isr_map[irq] = handler;
	_interrupt_switch.EnableGlobalInterrupt();
}

void bsp::IsrManager::RemoveIsr(uint32_t irq)
{
	_interrupt_switch.DisableGlobalInterrupt();
	_isr_map.erase(irq);
	_interrupt_switch.EnableGlobalInterrupt();
}
