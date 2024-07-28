#pragma once
#include <bsp-interface/di.h>
#include <bsp-interface/interrupt/IExtiManager.h>

namespace bsp
{
	inline void TestExtiManager(int line_id)
	{
		DI_ExtiManager().Register(
			line_id,
			[]()
			{
				DI_RedDigitalLed().Toggle();
			});

		while (true)
		{
		}
	}
}
