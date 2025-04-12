#pragma once
#include "base/peripheral/led/IDigitalLed.h"
#include "bsp-interface/di/key.h"

namespace bsp
{
	inline void TestKeyScanner()
	{
		while (true)
		{
			bsp::di::key::KeyScanner().ScanKeys();
			if (bsp::di::key::KeyScanner().HasKeyDownEvent("key0"))
			{
				base::led::RedDigitalLed().Toggle();
			}

			if (bsp::di::key::KeyScanner().HasKeyDownEvent("key1"))
			{
				base::led::GreenDigitalLed().Toggle();
			}
		}
	}

} // namespace bsp
