#pragma once
#include "base/peripheral/led/IDigitalLed.h"
#include "base/peripheral/serial/ISerial.h"
#include <stdexcept>

namespace bsp
{
	inline void TestSerial()
	{
		base::serial::ISerial *serial = base::serial::SerialCollection().Get("serial");
		if (serial == nullptr)
		{
			throw std::runtime_error{"找不到名为 serial 的串口"};
		}

		base::led::RedDigitalLed().TurnOn();
		serial->Start();
		std::unique_ptr<uint8_t[]> buffer{new uint8_t[128]};
		while (true)
		{
			int32_t have_read = serial->Read(buffer.get(), 0, 128);
			base::led::GreenDigitalLed().Toggle();
			base::led::RedDigitalLed().Toggle();
			serial->Write(buffer.get(), 0, have_read);
		}
	}
} // namespace bsp
