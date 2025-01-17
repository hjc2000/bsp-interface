#pragma once
#include <bsp-interface/di/interrupt.h>
#include <bsp-interface/di/led.h>

namespace bsp
{
	inline void TestExtiManager(int line_id)
	{
		DI_ExtiManager().Register(
			line_id,
			[]()
			{
				bsp::di::led::RedDigitalLed().Toggle();
			});

		while (true)
		{
		}
	}
} // namespace bsp
