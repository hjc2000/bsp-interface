#include "IConsole.h"
#include <base/string/ToHexString.h>

void bsp::IConsole::Write(char c)
{
	if (OutStream() == nullptr)
	{
		return;
	}

	OutStream()->Write(reinterpret_cast<uint8_t const *>(&c),
					   0,
					   1);
}

void bsp::IConsole::Write(char const *str)
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

void bsp::IConsole::Write(char const *str, int length)
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

void bsp::IConsole::Write(std::string const &str)
{
	Write(str.c_str());
}

void bsp::IConsole::Write(base::ReadOnlySpan const &o)
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

void bsp::IConsole::Write(void *p)
{
	Write(base::ToHexString(p));
}

void bsp::IConsole::WriteLine()
{
	Write("\n");
}

void bsp::IConsole::WriteLine(char const *str)
{
	Write(str);
	WriteLine();
}

void bsp::IConsole::WriteLine(std::string const &str)
{
	Write(str);
	WriteLine();
}

void bsp::IConsole::WriteLine(base::ICanToString const &o)
{
	WriteLine(o.ToString());
}

void bsp::IConsole::WriteLine(void *p)
{
	WriteLine(base::ToHexString(p));
}

void bsp::IConsole::WriteError() noexcept
{
	try
	{
		WriteLine();
	}
	catch (...)
	{
	}
}

void bsp::IConsole::WriteError(char const *str) noexcept
{
	try
	{
		WriteLine(str);
	}
	catch (...)
	{
	}
}

void bsp::IConsole::WriteError(std::string const &str) noexcept
{
	try
	{
		WriteLine(str);
	}
	catch (...)
	{
	}
}

void bsp::IConsole::WriteError(base::ICanToString const &o) noexcept
{
	try
	{
		WriteLine(o);
	}
	catch (...)
	{
	}
}
