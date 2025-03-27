#pragma once
#include "base/task/delay.h"
#include <bsp-interface/di/independent-watch-dog.h>
#include <bsp-interface/di/key.h>
#include <bsp-interface/di/led.h>

#ifndef No_Build_Test
namespace bsp
{
	inline void TestIndependentWatchDog()
	{
		base::task::Delay(std::chrono::milliseconds{500});
		bsp::di::led::RedDigitalLed().TurnOn();
		DI_IndependentWatchDog().Open(std::chrono::milliseconds(1000));
		while (true)
		{
			bsp::di::key::KeyScanner().ScanKeys();
			if (bsp::di::key::KeyScanner().HasKeyDownEvent("key0"))
			{
				DI_IndependentWatchDog().Feed();
			}
		}
	}

} // namespace bsp
#endif
