#include "IExpandedIoPort.h"
#include <bit>

bool bsp::IExpandedIoPort::ReadBit(int index)
{
    uint8_t data = ReadByte(index / 8);
    uint8_t mask = 0x1 << (index % 8);
    return data & mask;
}

void bsp::IExpandedIoPort::WriteBit(int index, bool value)
{
    uint8_t byte = ReadByte(index / 8);
    uint8_t mask = 0x1 << (index % 8);
    if (value)
    {
        byte |= mask;
    }
    else
    {
        byte &= ~mask;
    }

    WriteByte(index / 8, byte);
}

void bsp::IExpandedIoPort::ToggleBit(int index)
{
    bool bit = ReadBit(index);
    WriteBit(index, !bit);
}

void bsp::IExpandedIoPort::Read(int addr, base::Span const &span)
{
    for (int i = 0; i < span.Size(); i++)
    {
        span[i] = ReadByte(addr + i);
    }
}

uint16_t bsp::IExpandedIoPort::ReadUInt16(int index)
{
    uint16_t data = 0;

    base::Span span{
        reinterpret_cast<uint8_t *>(&data),
        sizeof(data),
    };

    Read(index * 2, span);

    /* 刚才的操作方式是低字节放到数组的低索引处，这是小端序，
     * 如果本机字节序是大端序，需要翻转。
     */
    if (std::endian::native == std::endian::big)
    {
        span.Reverse();
    }

    return data;
}

uint32_t bsp::IExpandedIoPort::ReadUInt32(int index)
{
    uint32_t data = 0;

    base::Span span{
        reinterpret_cast<uint8_t *>(&data),
        sizeof(data),
    };

    Read(index * 2, span);

    /* 刚才的操作方式是低字节放到数组的低索引处，这是小端序，
     * 如果本机字节序是大端序，需要翻转。
     */
    if (std::endian::native == std::endian::big)
    {
        span.Reverse();
    }

    return data;
}

uint64_t bsp::IExpandedIoPort::ReadUInt64(int index)
{
    uint64_t data = 0;

    base::Span span{
        reinterpret_cast<uint8_t *>(&data),
        sizeof(data),
    };

    Read(index * 2, span);

    /* 刚才的操作方式是低字节放到数组的低索引处，这是小端序，
     * 如果本机字节序是大端序，需要翻转。
     */
    if (std::endian::native == std::endian::big)
    {
        span.Reverse();
    }

    return data;
}
