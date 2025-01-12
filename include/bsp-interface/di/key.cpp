#include "key.h"
#include <bsp-interface/di/interrupt.h>
#include <bsp-interface/TaskSingletonGetter.h>
#include <KeyScanner.h>

namespace
{
	class Getter :
		public bsp::TaskSingletonGetter<bsp::KeyScanner>
	{
	public:
		std::unique_ptr<bsp::KeyScanner> Create() override
		{
			return std::unique_ptr<bsp::KeyScanner>{new bsp::KeyScanner{}};
		}
	};
} // namespace

bsp::IKeyScanner &DI_KeyScanner()
{
	Getter g;
	return g.Instance();
}
