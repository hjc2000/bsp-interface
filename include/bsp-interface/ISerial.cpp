#include "ISerial.h"

using namespace bsp;

uint32_t bsp::ISerial::CalculateFramesBaudCount(uint32_t frame_count)
{
	uint32_t baud_count = 0;
	baud_count += 1 * frame_count;			// 1 位起始位
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

#pragma region Stream
bool ISerial::CanRead()
{
	return true;
}

bool ISerial::CanWrite()
{
	return true;
}

bool ISerial::CanSeek()
{
	return false;
}

int64_t ISerial::Length()
{
	return 0;
}

void ISerial::SetLength(int64_t value)
{
	// 不支持的操作
}

void ISerial::Flush()
{
	// Write 方法利用 DMA 直接发送缓冲区，本类没有内部缓冲区，不需要冲洗。
}

int64_t ISerial::Position()
{
	return 0;
}

void ISerial::SetPosition(int64_t value)
{
	// 不支持的操作。
}
#pragma endregion
