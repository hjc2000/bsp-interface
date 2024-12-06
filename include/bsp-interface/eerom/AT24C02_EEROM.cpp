#include "AT24C02_EEROM.h"
#include <bsp-interface/di/delayer.h>

bsp::AT24C02_EEROM::AT24C02_EEROM(bsp::IIicHost *host)
{
    _iic_host = host;
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

void bsp::AT24C02_EEROM::Read(int32_t addr, base::Span const &span)
{
    if (addr + span.Size() > Size())
    {
        throw std::out_of_range{"要从 EEROM 读取的数据超出储存器范围。"};
    }

    for (int i = 0; i < span.Size(); i++)
    {
        span[i] = ReadByte(addr + i);
    }
}

void bsp::AT24C02_EEROM::Read(int32_t addr, uint8_t *buffer, int32_t offset, int32_t count)
{
    Read(addr, base::Span{buffer + offset, count});
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

void bsp::AT24C02_EEROM::Write(int32_t addr, base::ReadOnlySpan const &span)
{
    if (addr + span.Size() > Size())
    {
        throw std::out_of_range{"要写入到 EEROM 的数据超出储存器范围。"};
    }

    for (int i = 0; i < span.Size(); i++)
    {
        WriteByte(addr + i, span[i]);
    }
}

void bsp::AT24C02_EEROM::Write(int32_t addr, uint8_t const *buffer, int32_t offset, int32_t count)
{
    Write(addr, base::ReadOnlySpan{buffer + offset, count});
}
