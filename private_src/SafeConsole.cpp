#include "SafeConsole.h"
#include <base/di/SingletonGetter.h>
#include <base/string/ToHexString.h>
#include <bsp-interface/di/interrupt.h>

bsp::SafeConsole &bsp::SafeConsole::Instance()
{
	class Getter :
		public base::SingletonGetter<SafeConsole>
	{
	public:
		std::unique_ptr<SafeConsole> Create() override
		{
			return std::unique_ptr<SafeConsole>{new bsp::SafeConsole{}};
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

std::shared_ptr<base::Stream> bsp::SafeConsole::OutStream()
{
	base::LockGuard g{*_lock};
	return Console::Instance().OutStream();
}

void bsp::SafeConsole::SetOutStream(std::shared_ptr<base::Stream> value)
{
	base::LockGuard g{*_lock};
	Console::Instance().SetOutStream(value);
}

void bsp::SafeConsole::Write(char c)
{
	base::LockGuard g{*_lock};
	Console::Instance().Write(c);
}

void bsp::SafeConsole::Write(char const *str)
{
	base::LockGuard g{*_lock};
	Console::Instance().Write(str);
}

void bsp::SafeConsole::Write(char const *str, int length)
{
	base::LockGuard g{*_lock};
	Console::Instance().Write(str, length);
}

void bsp::SafeConsole::Write(std::string const &str)
{
	base::LockGuard g{*_lock};
	Console::Instance().Write(str);
}

void bsp::SafeConsole::Write(base::ReadOnlySpan const &o)
{
	base::LockGuard g{*_lock};
	Console::Instance().Write(o);
}

void bsp::SafeConsole::Write(void *p)
{
	base::LockGuard g{*_lock};
	Console::Instance().Write(p);
}

void bsp::SafeConsole::WriteLine()
{
	base::LockGuard g{*_lock};
	Console::Instance().WriteLine();
}

void bsp::SafeConsole::WriteLine(char const *str)
{
	base::LockGuard g{*_lock};
	Console::Instance().WriteLine(str);
}

void bsp::SafeConsole::WriteLine(std::string const &str)
{
	base::LockGuard g{*_lock};
	Console::Instance().WriteLine(str);
}

void bsp::SafeConsole::WriteLine(base::ICanToString const &o)
{
	base::LockGuard g{*_lock};
	Console::Instance().WriteLine(o);
}

void bsp::SafeConsole::WriteLine(void *p)
{
	base::LockGuard g{*_lock};
	Console::Instance().WriteLine(p);
}

void bsp::SafeConsole::WriteError() noexcept
{
	base::LockGuard g{*_lock};
	Console::Instance().WriteError();
}

void bsp::SafeConsole::WriteError(char const *str) noexcept
{
	base::LockGuard g{*_lock};
	Console::Instance().WriteError(str);
}

void bsp::SafeConsole::WriteError(std::string const &str) noexcept
{
	base::LockGuard g{*_lock};
	Console::Instance().WriteError(str);
}

void bsp::SafeConsole::WriteError(base::ICanToString const &o) noexcept
{
	base::LockGuard g{*_lock};
	Console::Instance().WriteError(o);
}
