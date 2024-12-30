#include "IEthernetController.h"
#include <base/container/Array.h>

void bsp::IEthernetController::Send(base::ReadOnlySpan const &span)
{
	Send(base::Array<base::ReadOnlySpan, 1>{span});
}
