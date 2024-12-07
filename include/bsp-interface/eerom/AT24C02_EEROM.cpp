#include "AT24C02_EEROM.h"
#include <bsp-interface/di/delayer.h>

bsp::AT24C02_EEROM::AT24C02_EEROM(std::string const &name, bsp::IIicHost *host)
{
    _name = name;
    _iic_host = host;

    /* 这里暂时这么定
     * 每个基于 IIC 的设备类都需要根据自己的能力设置 SCL 周期和 ACK 信号的等待超时
     * 周期数。
     */
    _iic_host->SetSclCycleWhenGreater(std::chrono::microseconds{4});
    _iic_host->SetWaitingForAckTimeoutCycleCountWhenGreater(100);
}

std::string bsp::AT24C02_EEROM::Name() const
{
    return _name;
}

int32_t bsp::AT24C02_EEROM::Size() const
{
    return 256;
}

uint8_t bsp::AT24C02_EEROM::ReadByte(int32_t addr)
{
    _iic_host->SendStartingSignal();
    _iic_host->SendByte(0XA0 + ((addr / 256) << 1)); // 发送器件地址0XA0,写数据
    _iic_host->SendByte(addr % 256);                 // 发送低地址
    _iic_host->SendStartingSignal();
    _iic_host->SendByte(0XA1); // 进入接收模式
    uint8_t data = _iic_host->ReceiveByte(1);
    _iic_host->SendStoppingSignal();
    return data;
}

void bsp::AT24C02_EEROM::WriteByte(int32_t addr, uint8_t data)
{
    _iic_host->SendStartingSignal();
    _iic_host->SendByte(0XA0 + ((addr / 256) << 1)); // 发送器件地址0XA0,写数据
    _iic_host->SendByte(addr % 256);                 // 发送低地址
    _iic_host->SendByte(data);                       // 发送字节
    _iic_host->SendStoppingSignal();                 // 产生一个停止条件
    DI_Delayer().Delay(std::chrono::milliseconds{10});
}
