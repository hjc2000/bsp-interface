#include "Console.h"
#include <base/di/SingletonGetter.h>
#include <base/string/ToHexString.h>
#include <bsp-interface/di/interrupt.h>

bsp::Console &bsp::Console::Instance()
{
	class Getter :
		public base::SingletonGetter<Console>
	{
	public:
		std::unique_ptr<Console> Create() override
		{
			return std::unique_ptr<Console>{new bsp::Console{}};
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

void bsp::Console::Write(char c)
{
	if (OutStream() == nullptr)
	{
		return;
	}

	OutStream()->Write(reinterpret_cast<uint8_t const *>(&c),
					   0,
					   1);
}

void bsp::Console::Write(char const *str)
{
	if (OutStream() == nullptr)
	{
		return;
	}

	int32_t end_index = 0;
	while (true)
	{
		if (str[end_index] == '\0')
		{
			break;
		}

		if (end_index == INT32_MAX)
		{
			break;
		}

		end_index++;
	}

	if (end_index <= 0)
	{
		return;
	}

	OutStream()->Write(reinterpret_cast<uint8_t const *>(str),
					   0,
					   end_index);
}

void bsp::Console::Write(char const *str, int length)
{
	if (OutStream() == nullptr)
	{
		return;
	}

	if (str == nullptr)
	{
		return;
	}

	if (length <= 0)
	{
		return;
	}

	OutStream()->Write(reinterpret_cast<uint8_t const *>(str),
					   0,
					   length);
}

void bsp::Console::Write(std::string const &str)
{
	Write(str.c_str());
}

void bsp::Console::Write(base::ReadOnlySpan const &o)
{
	for (int i = 0; i < o.Size(); i++)
	{
		Write(std::to_string(o[i]));
		Write("  ");
		if (i % 20 == 0 && i != 0)
		{
			WriteLine();
		}
	}
}

void bsp::Console::Write(void *p)
{
	Write(base::ToHexString(p));
}

void bsp::Console::WriteLine()
{
	Write("\n");
}

void bsp::Console::WriteLine(char const *str)
{
	Write(str);
	WriteLine();
}

void bsp::Console::WriteLine(std::string const &str)
{
	Write(str);
	WriteLine();
}

void bsp::Console::WriteLine(base::ICanToString const &o)
{
	WriteLine(o.ToString());
}

void bsp::Console::WriteLine(void *p)
{
	WriteLine(base::ToHexString(p));
}

void bsp::Console::WriteError() noexcept
{
	try
	{
		WriteLine();
	}
	catch (...)
	{
	}
}

void bsp::Console::WriteError(char const *str) noexcept
{
	try
	{
		WriteLine(str);
	}
	catch (...)
	{
	}
}

void bsp::Console::WriteError(std::string const &str) noexcept
{
	try
	{
		WriteLine(str);
	}
	catch (...)
	{
	}
}

void bsp::Console::WriteError(base::ICanToString const &o) noexcept
{
	try
	{
		WriteLine(o);
	}
	catch (...)
	{
	}
}
