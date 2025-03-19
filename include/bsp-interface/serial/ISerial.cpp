#include "ISerial.h"

uint32_t bsp::serial::ISerial::FramesBaudCount(uint32_t frame_count) const
{
	uint32_t baud_count = 0;

	// 1 位起始位
	baud_count += 1 * frame_count;

	// DataBits().Value() 位数据位
	baud_count += DataBits() * frame_count;

	if (Parity() != bsp::serial::property::Parity::None)
	{
		// 1 位校验位
		baud_count += 1 * frame_count;
	}

	// 停止位
	switch (StopBits())
	{
	case bsp::serial::property::StopBits::ZeroPointFive:
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
	case bsp::serial::property::StopBits::One:
		{
			baud_count += 1 * frame_count;
			break;
		}
	case bsp::serial::property::StopBits::OnePointFive:
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
	case bsp::serial::property::StopBits::Tow:
		{
			baud_count += 2 * frame_count;
			break;
		}
	}

	return baud_count;
}

/* #region Open */

void bsp::serial::ISerial::Open()
{
	Open(bsp::serial::property::Direction::RX_TX,
		 bsp::serial::property::BaudRate{115200},
		 bsp::serial::property::DataBits{8},
		 bsp::serial::property::Parity::None,
		 bsp::serial::property::StopBits::One,
		 bsp::serial::property::HardwareFlowControl::None);
}

void bsp::serial::ISerial::Open(bsp::serial::property::BaudRate const &baud_rate)
{
	Open(bsp::serial::property::Direction::RX_TX,
		 baud_rate,
		 bsp::serial::property::DataBits{8},
		 bsp::serial::property::Parity::None,
		 bsp::serial::property::StopBits::One,
		 bsp::serial::property::HardwareFlowControl::None);
}

/* #endregion */

/* #region Stream */

bool bsp::serial::ISerial::CanRead() const
{
	return true;
}

bool bsp::serial::ISerial::CanWrite() const
{
	return true;
}

bool bsp::serial::ISerial::CanSeek() const
{
	return false;
}

int64_t bsp::serial::ISerial::Length() const
{
	return 0;
}

void bsp::serial::ISerial::SetLength(int64_t value)
{
	// 不支持的操作
}

void bsp::serial::ISerial::Flush()
{
	// Write 方法利用 DMA 直接发送缓冲区，本类没有内部缓冲区，不需要冲洗。
}

int64_t bsp::serial::ISerial::Position() const
{
	return 0;
}

void bsp::serial::ISerial::SetPosition(int64_t value)
{
	// 不支持的操作。
}

/* #endregion */
