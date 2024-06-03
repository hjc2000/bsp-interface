#include"ISerial.h"

uint64_t bsp::ISerial::BaudTicks(uint32_t baud_count, uint32_t tick_freq)
{
	/*
	* baud_interval = 1 / baud_rate
	* tick_interval = 1 / tick_frequency
	*
	* tick_count = baud_count * baud_interval / tick_interval
	* tick_count = baud_count * (1 / baud_rate) / (1 / tick_frequency)
	* tick_count = baud_count * (1 / baud_rate) * tick_frequency
	* tick_count = baud_count * tick_frequency / baud_rate
	*/

	uint64_t tick_count = baud_count * tick_freq / BaudRate();
	return tick_count;
}

uint64_t bsp::ISerial::FrameTicks(uint32_t frame_count, uint32_t tick_freq)
{
	uint32_t baud_count = 0;
	baud_count += 1 * frame_count; // 1 位起始位
	baud_count += DataBits() * frame_count; // 数据位
	if (Parity() != ParityOption::None)
	{
		baud_count += 1 * frame_count; // 1 位校验位
	}

	switch (StopBits())
	{
	case StopBitsOption::None:
		{
			break;
		}
	case StopBitsOption::ZeroPointFive:
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
	case StopBitsOption::One:
		{
			baud_count += 1 * frame_count;
			break;
		}
	case StopBitsOption::OnePointFive:
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
	case StopBitsOption::Tow:
		{
			baud_count += 2 * frame_count;
			break;
		}
	}

	return BaudTicks(baud_count, tick_freq);
}
