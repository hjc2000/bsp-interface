#include"Console.h"

using namespace bsp;

void bsp::Console::Write(std::string const &str)
{
	if (_out_stream == nullptr)
	{
		return;
	}

	_out_stream->Write((uint8_t *)(str.c_str()), 0, str.length());
}

void bsp::Console::WriteLine(std::string const &str)
{
	Write(str);
	Write("\n");
}

void bsp::Console::Write(char const *str)
{
	if (_out_stream == nullptr)
	{
		return;
	}

	int32_t index_of_white_char = 0;
	while (true)
	{
		if (str[index_of_white_char] == '\0')
		{
			break;
		}

		if (index_of_white_char == INT32_MAX)
		{
			break;
		}

		index_of_white_char++;
	}

	_out_stream->Write((uint8_t const *)(str), 0, index_of_white_char);
}

void bsp::Console::WriteLine(char const *str)
{
	Write(str);
	Write("\n");
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
