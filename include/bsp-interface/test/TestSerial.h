#pragma once
#include "base/peripheral/serial/Serial.h"

namespace bsp
{
	inline void TestSerial()
	{
		base::serial::Serial serial{1};
		// base::led::RedDigitalLed().TurnOn();
		serial.Start();
		std::unique_ptr<uint8_t[]> buffer{new uint8_t[128]};
		while (true)
		{
			int32_t have_read = serial.Read(buffer.get(), 0, 128);
			// base::led::GreenDigitalLed().Toggle();
			// base::led::RedDigitalLed().Toggle();
			serial.Write(buffer.get(), 0, have_read);
		}
	}
} // namespace bsp
