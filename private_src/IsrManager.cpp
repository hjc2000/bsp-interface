#include "IsrManager.h"
#include <bsp-interface/di/task.h>

using namespace bsp;

IsrManager &bsp::IsrManager::Instance()
{
	class Getter :
		public bsp::TaskSingletonGetter<IsrManager>
	{
	public:
		std::unique_ptr<IsrManager> Create() override
		{
			return std::unique_ptr<IsrManager>{new IsrManager{}};
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
	_isr_map[irq] = handler;
}

void bsp::IsrManager::RemoveIsr(uint32_t irq) noexcept
{
	bsp::TaskGuard g;
	_isr_map.erase(irq);
}
