#include "key.h"
#include <base/di/SingletonGetter.h>
#include <bsp-interface/di/interrupt.h>
#include <KeyScanner.h>

namespace
{
    class Getter :
        public base::SingletonGetter<bsp::KeyScanner>
    {
    public:
        std::unique_ptr<bsp::KeyScanner> Create() override
        {
            return std::unique_ptr<bsp::KeyScanner>{new bsp::KeyScanner{}};
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
} // namespace

bsp::IKeyScanner &DI_KeyScanner()
{
    Getter g;
    return g.Instance();
}
