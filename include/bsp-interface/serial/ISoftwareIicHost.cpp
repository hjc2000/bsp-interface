#include "ISoftwareIicHost.h"
#include <bsp-interface/di/delayer.h>

void bsp::ISoftwareIicHost::SendStartingSignal()
{
    ChangeSDADirection(bsp::ISoftwareIicHost_SDADirection::Output);
    WriteSDA(true);
    WriteSCL(true);
    DI_Delayer().Delay(std::chrono::microseconds{4});
    WriteSDA(false);
    DI_Delayer().Delay(std::chrono::microseconds{4});
    WriteSCL(false);
}

void bsp::ISoftwareIicHost::SendStoppingSignal()
{
    ChangeSDADirection(bsp::ISoftwareIicHost_SDADirection::Output);
    WriteSCL(false);
    WriteSDA(false);
    DI_Delayer().Delay(std::chrono::microseconds{4});
    WriteSCL(true);
    WriteSDA(true);
    DI_Delayer().Delay(std::chrono::microseconds{4});
}

void bsp::ISoftwareIicHost::SendAcknowledgment()
{
    WriteSCL(false);
    ChangeSDADirection(bsp::ISoftwareIicHost_SDADirection::Output);
    WriteSDA(false);
    DI_Delayer().Delay(std::chrono::microseconds{2});
    WriteSCL(true);
    DI_Delayer().Delay(std::chrono::microseconds{2});
    WriteSCL(false);
}

void bsp::ISoftwareIicHost::SendNotAcknowledgment()
{
    WriteSCL(false);
    ChangeSDADirection(bsp::ISoftwareIicHost_SDADirection::Output);
    WriteSDA(true);
    DI_Delayer().Delay(std::chrono::microseconds{2});
    WriteSCL(true);
    DI_Delayer().Delay(std::chrono::microseconds{2});
    WriteSCL(false);
}

bool bsp::ISoftwareIicHost::WaitForAcknowledgment()
{
    ChangeSDADirection(bsp::ISoftwareIicHost_SDADirection::Input);
    WriteSDA(true);
    DI_Delayer().Delay(std::chrono::microseconds{1});
    WriteSCL(true);
    DI_Delayer().Delay(std::chrono::microseconds{1});

    int retry_times = 0;
    while (ReadSDA())
    {
        retry_times++;
        if (retry_times > 250)
        {
            SendStoppingSignal();
            return false;
        }
    }

    WriteSCL(0);
    return true;
}

void bsp::ISoftwareIicHost::SendBit(bool value)
{
    ChangeSDADirection(bsp::ISoftwareIicHost_SDADirection::Output);
    WriteSCL(false);
    WriteSDA(value);
    DI_Delayer().Delay(std::chrono::microseconds{2});
    WriteSCL(true);
    DI_Delayer().Delay(std::chrono::microseconds{2});
    WriteSCL(false);
    DI_Delayer().Delay(std::chrono::microseconds{2});
}

bool bsp::ISoftwareIicHost::SendByte(uint8_t value)
{
    for (int i = 0; i < 8; i++)
    {
        // 取出最高位。IIC 是从最高位开始发送。
        bool bit = value & 0x80;
        SendBit(bit);

        // 将次高位变成最高位。
        value <<= 1;
    }

    return WaitForAcknowledgment();
}
