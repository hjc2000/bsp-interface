#include "ISoftwareIicHost.h"
#include <bsp-interface/di/delayer.h>

void bsp::ISoftwareIicHost::SendAcknowledgment()
{
    WriteSCL(false);
    ChangeSDADirection(bsp::ISoftwareIicHost_SDADirection::Output);
    WriteSDA(false);
    DI_Delayer().Delay(_scl_cycle / 2);
    WriteSCL(true);
    DI_Delayer().Delay(_scl_cycle / 2);
    WriteSCL(false);
}

void bsp::ISoftwareIicHost::SendNotAcknowledgment()
{
    WriteSCL(false);
    ChangeSDADirection(bsp::ISoftwareIicHost_SDADirection::Output);
    WriteSDA(true);
    DI_Delayer().Delay(_scl_cycle / 2);
    WriteSCL(true);
    DI_Delayer().Delay(_scl_cycle / 2);
    WriteSCL(false);
}

bool bsp::ISoftwareIicHost::WaitForAcknowledgment()
{
    ChangeSDADirection(bsp::ISoftwareIicHost_SDADirection::Input);
    WriteSDA(true);
    DI_Delayer().Delay(_scl_cycle / 2);
    WriteSCL(true);
    DI_Delayer().Delay(_scl_cycle / 2);

    int retry_times = 0;
    while (ReadSDA())
    {
        retry_times++;
        DI_Delayer().Delay(_scl_cycle / 2);
        if (retry_times > _waiting_for_ack_timeout_cycle)
        {
            SendStoppingSignal();
            return false;
        }
    }

    WriteSCL(false);
    return true;
}

void bsp::ISoftwareIicHost::SendBit(bool value)
{
    ChangeSDADirection(bsp::ISoftwareIicHost_SDADirection::Output);
    WriteSCL(false);
    WriteSDA(value);
    DI_Delayer().Delay(_scl_cycle / 2);
    WriteSCL(true);
    DI_Delayer().Delay(_scl_cycle / 2);
    WriteSCL(false);
    DI_Delayer().Delay(_scl_cycle / 2);
}

bool bsp::ISoftwareIicHost::ReceiveBit()
{
    ChangeSDADirection(bsp::ISoftwareIicHost_SDADirection::Input);
    WriteSCL(false);
    DI_Delayer().Delay(_scl_cycle / 2);
    WriteSCL(true);
    bool bit = ReadSDA();
    DI_Delayer().Delay(_scl_cycle / 2);
    return bit;
}

void bsp::ISoftwareIicHost::SendStartingSignal()
{
    ChangeSDADirection(bsp::ISoftwareIicHost_SDADirection::Output);
    WriteSDA(true);
    WriteSCL(true);
    DI_Delayer().Delay(_scl_cycle);
    WriteSDA(false);
    DI_Delayer().Delay(_scl_cycle);
    WriteSCL(false);
}

void bsp::ISoftwareIicHost::SendStoppingSignal()
{
    ChangeSDADirection(bsp::ISoftwareIicHost_SDADirection::Output);
    WriteSCL(false);
    WriteSDA(false);
    DI_Delayer().Delay(_scl_cycle);
    WriteSCL(true);
    WriteSDA(true);
    DI_Delayer().Delay(_scl_cycle);
}

void bsp::ISoftwareIicHost::SendByte(uint8_t value)
{
    for (int i = 0; i < 8; i++)
    {
        // 取出最高位。IIC 是从最高位开始发送。
        bool bit = value & 0x80;
        SendBit(bit);

        // 将次高位变成最高位。
        value <<= 1;
    }

    bool ack = WaitForAcknowledgment();
    if (!ack)
    {
        throw std::runtime_error{"IIC 接口 " + Name() + " 发送数据时未收到从机的应答信号"};
    }
}

uint8_t bsp::ISoftwareIicHost::ReceiveByte(bool send_nack)
{
    uint8_t data = 0;
    for (int i = 0; i < 8; i++)
    {
        bool bit = ReceiveBit();
        data <<= 1;
        if (bit)
        {
            data |= 0x1;
        }
    }

    if (send_nack)
    {
        SendNotAcknowledgment();
    }
    else
    {
        SendAcknowledgment();
    }

    return data;
}

std::chrono::microseconds bsp::ISoftwareIicHost::SclCycle() const
{
    return _scl_cycle;
}

void bsp::ISoftwareIicHost::SetSclCycle(std::chrono::microseconds value)
{
    _scl_cycle = value;
}

int bsp::ISoftwareIicHost::WaitingForAckTimeoutCycleCount() const
{
    return _waiting_for_ack_timeout_cycle;
}

void bsp::ISoftwareIicHost::SetWaitingForAckTimeoutCycleCount(int value)
{
    _waiting_for_ack_timeout_cycle = value;
}
