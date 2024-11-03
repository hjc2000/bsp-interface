#include "IConsole.h"

void bsp::IConsole::Write(char const *str)
{
    if (OutStream() == nullptr)
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

    OutStream()->Write((uint8_t const *)(str), 0, index_of_white_char);
}

void bsp::IConsole::Write(std::string const &str)
{
    if (OutStream() == nullptr)
    {
        return;
    }

    OutStream()->Write((uint8_t *)(str.c_str()), 0, str.length());
}

void bsp::IConsole::WriteLine(char const *str)
{
    Write(str);
    Write("\n");
}

void bsp::IConsole::WriteLine(std::string const &str)
{
    Write(str);
    Write("\n");
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
