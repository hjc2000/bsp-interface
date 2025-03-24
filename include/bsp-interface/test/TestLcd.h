#pragma once
#include "base/task/delay.h"
#include <bsp-interface/di/lcd.h>
#include <bsp-interface/di/led.h>

#ifndef No_Build_Test
namespace bsp
{
	inline void TestLcd()
	{
		bsp::di::led::GreenDigitalLed().TurnOn();
		DI_Lcd().DisplayOn();

		while (true)
		{
			base::Delay(std::chrono::seconds{1});
			for (uint32_t x = 0; x < DI_Lcd().Width(); x++)
			{
				for (uint32_t y = 0; y < DI_Lcd().Height(); y++)
				{
					DI_Lcd().DrawPoint(x, y, 0x07E0);
				}
			}

			base::Delay(std::chrono::seconds{1});
			DI_Lcd().Clear(bsp::Color::Black);
			bsp::di::led::RedDigitalLed().Toggle();
			base::Delay(std::chrono::seconds{1});
		}
	}
} // namespace bsp
#endif
