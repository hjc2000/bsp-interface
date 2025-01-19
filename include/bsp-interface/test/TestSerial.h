#pragma once
#include <bsp-interface/di/led.h>
#include <bsp-interface/di/serial.h>
#include <stdexcept>

namespace bsp
{
	inline void TestSerial()
	{
		bsp::serial::ISerial *serial = bsp::di::serial::SerialCollection().Get("serial");
		if (serial == nullptr)
		{
			throw std::runtime_error{"找不到名为 serial 的串口"};
		}

		bsp::di::led::RedDigitalLed().TurnOn();
		serial->Open();
		std::unique_ptr<uint8_t[]> buffer{new uint8_t[128]};
		while (true)
		{
			int32_t have_read = serial->Read(buffer.get(), 0, 128);
			bsp::di::led::GreenDigitalLed().Toggle();
			bsp::di::led::RedDigitalLed().Toggle();
			serial->Write(buffer.get(), 0, have_read);
		}
	}
} // namespace bsp
