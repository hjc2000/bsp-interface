#include"IIsrManager.h"

using namespace bsp;

std::function<void()> const &bsp::IIsrManager::GetIrqHandlerFromIsr(uint32_t irq)
{
	return HandlerMap()[irq];
}

void bsp::IIsrManager::SetIrqHandler(uint32_t irq, std::function<void()> handler)
{
	DisableInterrupt(irq);
	HandlerMap()[irq] = handler;
	EnableInterrupt(irq);
}
