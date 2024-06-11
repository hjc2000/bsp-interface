#include"IIsrManager.h"

using namespace bsp;

void bsp::IIsrManager::AddHandler(uint32_t irq, std::function<void()> handler)
{
	DisableInterrupt(irq);
	HandlerMap()[irq] = handler;
	EnableInterrupt(irq);
}

void bsp::IIsrManager::RemoveHandler(uint32_t irq)
{
	DisableInterrupt(irq);
	HandlerMap().erase(irq);
	EnableInterrupt(irq);
}
