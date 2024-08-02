#pragma once
#include <bsp-interface/di.h>

namespace bsp
{
	inline void TestSerial()
	{
		bsp::ISerial *serial = *DI_SerialList().begin();
		DI_RedDigitalLed().TurnOn();
		serial->Open(*DICreate_ISerialOptions());
		std::unique_ptr<uint8_t[]> buffer{new uint8_t[128]};
		while (1)
		{
			int32_t have_read = serial->Read(buffer.get(), 0, 128);
			DI_GreenDigitalLed().Toggle();
			DI_RedDigitalLed().Toggle();
			serial->Write(buffer.get(), 0, have_read);
		}
	}
}
