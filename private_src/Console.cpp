#include "Console.h"
#include <base/di/SingletonGetter.h>
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
