#include "Console.h"
#include <base/string/ToHexString.h>
#include <bsp-interface/di/interrupt.h>

namespace
{
	class Init
	{
	public:
		Init()
		{
			bsp::Console::Instance();
		}
	};

	Init volatile _console_hjc_init{};

} // namespace

bsp::Console &bsp::Console::Instance()
{
	static bsp::Console o{};
	return o;
}

std::shared_ptr<base::Stream> bsp::Console::OutStream()
{
	return _out_stream;
}

void bsp::Console::SetOutStream(std::shared_ptr<base::Stream> value)
{
	_out_stream = value;
}
