#pragma once
#include <bsp-interface/di.h>

#ifndef No_Build_Test
namespace bsp
{
	inline void TestIndependentWatchDog()
	{
		DI_Delayer().Delay(std::chrono::milliseconds{500});
		DI_RedDigitalLed().TurnOn();
		DI_IndependentWatchDog().SetWatchDogTimeoutDuration(std::chrono::milliseconds(1000));

		while (true)
		{
			DI_KeyScanner().ScanKeys();
			if (DI_KeyScanner().HasKeyDownEvent(0))
			{
				DI_IndependentWatchDog().Feed();
			}
		}
	}

}
#endif
