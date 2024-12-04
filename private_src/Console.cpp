#include "Console.h"
#include <base/di/SingletonGetter.h>
#include <bsp-interface/di/interrupt.h>

using namespace bsp;

Console &bsp::Console::Instance()
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
            DI_InterruptSwitch().DisableGlobalInterrupt();
        }

        void Unlock() override
        {
            DI_InterruptSwitch().EnableGlobalInterrupt();
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

#include <bsp-interface/di/console.h>
#include <stdio.h>

extern "C"
{
    /// @brief stdio 底层会调用本函数。
    ///
    /// @param file 文件描述符
    /// @note 对于标准输出，file = 1，对于错误输出，file = 2。
    ///
    /// @param ptr
    /// @param len
    /// @return
    int _write(int file, char *ptr, int len)
    {
        try
        {
            DI_Console().Write(ptr, len);
            return len;
        }
        catch (...)
        {
            return EIO;
        }
    }
}
