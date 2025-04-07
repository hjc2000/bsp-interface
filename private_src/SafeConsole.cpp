#include "SafeConsole.h"
#include <base/string/ToHexString.h>
#include <bsp-interface/di/interrupt.h>
#include <bsp-interface/TaskSingletonGetter.h>

namespace
{
	class Init
	{
	public:
		Init()
		{
			bsp::SafeConsole::Instance();
		}
	};

	Init volatile _safe_console_hjc_init{};

} // namespace

bsp::SafeConsole &bsp::SafeConsole::Instance()
{
	static bsp::SafeConsole o{};
	return o;
}

std::shared_ptr<base::Stream> bsp::SafeConsole::OutStream()
{
	return _console->OutStream();
}

void bsp::SafeConsole::SetOutStream(std::shared_ptr<base::Stream> value)
{
	_console->SetOutStream(value);
}

void bsp::SafeConsole::Write(char c)
{
	base::LockGuard g{*_lock};
	_console->Write(c);
}

void bsp::SafeConsole::Write(char const *str)
{
	base::LockGuard g{*_lock};
	_console->Write(str);
}

void bsp::SafeConsole::Write(char const *str, int length)
{
	base::LockGuard g{*_lock};
	_console->Write(str, length);
}

void bsp::SafeConsole::Write(std::string const &str)
{
	base::LockGuard g{*_lock};
	_console->Write(str);
}

void bsp::SafeConsole::Write(base::ReadOnlySpan const &o)
{
	base::LockGuard g{*_lock};
	_console->Write(o);
}

void bsp::SafeConsole::Write(void const *p)
{
	base::LockGuard g{*_lock};
	_console->Write(p);
}

void bsp::SafeConsole::WriteLine()
{
	base::LockGuard g{*_lock};
	_console->WriteLine();
}

void bsp::SafeConsole::WriteLine(char const *str)
{
	base::LockGuard g{*_lock};
	_console->WriteLine(str);
}

void bsp::SafeConsole::WriteLine(std::string const &str)
{
	base::LockGuard g{*_lock};
	_console->WriteLine(str);
}

void bsp::SafeConsole::WriteLine(base::ICanToString const &o)
{
	base::LockGuard g{*_lock};
	_console->WriteLine(o);
}

void bsp::SafeConsole::WriteLine(void const *p)
{
	base::LockGuard g{*_lock};
	_console->WriteLine(p);
}

void bsp::SafeConsole::WriteError() noexcept
{
	base::LockGuard g{*_lock};
	_console->WriteError();
}

void bsp::SafeConsole::WriteError(char const *str) noexcept
{
	base::LockGuard g{*_lock};
	_console->WriteError(str);
}

void bsp::SafeConsole::WriteError(std::string const &str) noexcept
{
	base::LockGuard g{*_lock};
	_console->WriteError(str);
}

void bsp::SafeConsole::WriteError(base::ICanToString const &o) noexcept
{
	base::LockGuard g{*_lock};
	_console->WriteError(o);
}
