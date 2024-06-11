#include"IsrManager.h"

using namespace bsp;

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
	_interrupt_switch.DisableInterrupt(irq);
	_isr_map[irq] = handler;
	_interrupt_switch.EnableInterrupt(irq);
}

void bsp::IsrManager::RemoveHandler(uint32_t irq)
{
	_interrupt_switch.DisableInterrupt(irq);
	_isr_map.erase(irq);
}
