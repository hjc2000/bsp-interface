#pragma once
#include "base/peripheral/led/IDigitalLed.h"
#include "bsp-interface/di/interrupt.h"

namespace bsp
{
	inline void TestExtiManager(int line_id)
	{
		bsp::di::interrupt::ExtiManager().Register(
			line_id,
			[]()
			{
				base::led::RedDigitalLed().Toggle();
			});

		while (true)
		{
		}
	}
} // namespace bsp
