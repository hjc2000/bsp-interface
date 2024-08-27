#pragma once
#include <bsp-interface/di/led.h>
#include <bsp-interface/di/serial.h>
#include <stdexcept>

namespace bsp
{
    inline void TestSerial()
    {
        bsp::ISerial *serial = DI_SerialCollection().Get("serial");
        if (serial == nullptr)
        {
            throw std::runtime_error{"找不到名为 serial 的串口"};
        }

        DI_RedDigitalLed().TurnOn();
        serial->Open(*DICreate_ISerialOptions());
        std::unique_ptr<uint8_t[]> buffer{new uint8_t[128]};
        while (true)
        {
            int32_t have_read = serial->Read(buffer.get(), 0, 128);
            DI_GreenDigitalLed().Toggle();
            DI_RedDigitalLed().Toggle();
            serial->Write(buffer.get(), 0, have_read);
        }
    }
} // namespace bsp
