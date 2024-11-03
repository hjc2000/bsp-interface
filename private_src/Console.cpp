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
