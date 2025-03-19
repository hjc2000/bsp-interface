#pragma once
#include "bsp-interface/di/key.h"
#include "bsp-interface/di/led.h"

namespace bsp
{
	inline void TestKeyScanner()
	{
		while (true)
		{
			bsp::di::key::KeyScanner().ScanKeys();
			if (bsp::di::key::KeyScanner().HasKeyDownEvent("key0"))
			{
				bsp::di::led::RedDigitalLed().Toggle();
			}

			if (bsp::di::key::KeyScanner().HasKeyDownEvent("key1"))
			{
				bsp::di::led::GreenDigitalLed().Toggle();
			}
		}
	}

} // namespace bsp
