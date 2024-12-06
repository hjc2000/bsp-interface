#include "IEEROM.h"

uint16_t bsp::IEEROM::ReadUint16(int32_t addr)
{
    uint16_t data;
    Read(addr, base::Span{reinterpret_cast<uint8_t *>(&data), sizeof(data)});
    return data;
}

uint32_t bsp::IEEROM::ReadUint32(int32_t addr)
{
    uint32_t data;
    Read(addr, base::Span{reinterpret_cast<uint8_t *>(&data), sizeof(data)});
    return data;
}

uint64_t bsp::IEEROM::ReadUint64(int32_t addr)
{
    uint64_t data;
    Read(addr, base::Span{reinterpret_cast<uint8_t *>(&data), sizeof(data)});
    return data;
}

void bsp::IEEROM::Read(int32_t addr, base::Span const &span)
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

void bsp::IEEROM::Read(int32_t addr, uint8_t *buffer, int32_t offset, int32_t count)
{
    Read(addr, base::Span{buffer + offset, count});
}

void bsp::IEEROM::Write(int32_t addr, base::ReadOnlySpan const &span)
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

void bsp::IEEROM::Write(int32_t addr, uint8_t const *buffer, int32_t offset, int32_t count)
{
    Write(addr, base::ReadOnlySpan{buffer + offset, count});
}
