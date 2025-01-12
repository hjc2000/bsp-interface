#include "Console.h"
#include <base/string/ToHexString.h>
#include <bsp-interface/di/interrupt.h>
#include <bsp-interface/TaskSingletonGetter.h>

bsp::Console &bsp::Console::Instance()
{
	class Getter :
		public bsp::TaskSingletonGetter<bsp::Console>
	{
	public:
		std::unique_ptr<bsp::Console> Create() override
		{
			return std::unique_ptr<bsp::Console>{new bsp::Console{}};
		}

		void Lock() override
		{
			DI_DisableGlobalInterrupt();
		}

		void Unlock() override
		{
			DI_EnableGlobalInterrupt();
		}
	};

	Getter g;
	return g.Instance();
}

std::shared_ptr<base::Stream> bsp::Console::OutStream()
{
	return _out_stream;
}

void bsp::Console::SetOutStream(std::shared_ptr<base::Stream> value)
{
	_out_stream = value;
}
