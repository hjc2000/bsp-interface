#include "IEthernetPort.h"
#include <base/container/Array.h>
#include <bsp-interface/di/console.h>

void bsp::IEthernetPort::Send(base::ReadOnlySpan const &span)
{
	Send(base::Array<base::ReadOnlySpan, 1>{span});
}
