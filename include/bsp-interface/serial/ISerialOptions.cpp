#include "ISerialOptions.h"

uint32_t bsp::ISerialOptions::CalculateFramesBaudCount(uint32_t frame_count) const
{
    uint32_t baud_count = 0;
    baud_count += 1 * frame_count;          // 1 位起始位
    baud_count += DataBits() * frame_count; // 数据位
    if (Parity() != bsp::ISerialParity::None)
    {
        baud_count += 1 * frame_count; // 1 位校验位
    }

    // 停止位
    switch (StopBits())
    {
    case bsp::ISerialStopBits::ZeroPointFive:
        {
            // 每 2 个帧占用 1 个位。
            baud_count += frame_count / 2;

            // 还剩余半个位，当成 1 位。
            if (frame_count % 2 > 0)
            {
                baud_count += 1;
            }

            break;
        }
    default:
    case bsp::ISerialStopBits::One:
        {
            baud_count += 1 * frame_count;
            break;
        }
    case bsp::ISerialStopBits::OnePointFive:
        {
            // 每 2 个帧占用 3 个位。
            baud_count += (frame_count / 2) * 3;

            // 还剩余 1.5 个位，当成 2 位。
            if (frame_count % 2 > 0)
            {
                baud_count += 2;
            }

            break;
        }
    case bsp::ISerialStopBits::Tow:
        {
            baud_count += 2 * frame_count;
            break;
        }
    }

    return baud_count;
}
