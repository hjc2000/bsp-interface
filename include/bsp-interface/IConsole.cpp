#include "IConsole.h"

void bsp::IConsole::WriteLine(std::string const &str)
{
    Write(str);
    Write("\n");
}

void bsp::IConsole::WriteLine(char const *str)
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
