#include "ST7789LcdDriver.h"
#include <bsp-interface/di/delayer.h>

using namespace bsp;

#pragma region ILcd

uint32_t bsp::ST7789LcdDriver::LcdDriverChipId()
{
	uint16_t id = 0;
	WriteCommand(0X04);
	uint16_t temp = ReadData(); // 第一次读取会读取到刚刚写入的命令 0x04
	temp = ReadData();          // 读到 0x85
	temp = ReadData();          // 读到 0x85
	id = temp << 8;
	temp = ReadData(); // 读到 0x52
	id |= temp;
	return id;
}

void bsp::ST7789LcdDriver::DisplayOn()
{
	bsp::di::Delayer().Delay(std::chrono::milliseconds{50});
	WriteCommand(0x11);
	bsp::di::Delayer().Delay(std::chrono::milliseconds{120});

	WriteCommand(0x36);
	WriteData(0x00);

	WriteCommand(0x3A);
	WriteData(0X05);

	WriteCommand(0xB2);
	WriteData(0x0C);
	WriteData(0x0C);
	WriteData(0x00);
	WriteData(0x33);
	WriteData(0x33);

	WriteCommand(0xB7);
	WriteData(0x35);

	WriteCommand(0xBB); /* vcom */
	WriteData(0x32);    /* 30 */

	WriteCommand(0xC0);
	WriteData(0x0C);

	WriteCommand(0xC2);
	WriteData(0x01);

	WriteCommand(0xC3); /* vrh */
	WriteData(0x10);    /* 17 0D */

	WriteCommand(0xC4); /* vdv */
	WriteData(0x20);    /* 20 */

	WriteCommand(0xC6);
	WriteData(0x0f);

	WriteCommand(0xD0);
	WriteData(0xA4);
	WriteData(0xA1);

	WriteCommand(0xE0); /* Set Gamma  */
	WriteData(0xd0);
	WriteData(0x00);
	WriteData(0x02);
	WriteData(0x07);
	WriteData(0x0a);
	WriteData(0x28);
	WriteData(0x32);
	WriteData(0X44);
	WriteData(0x42);
	WriteData(0x06);
	WriteData(0x0e);
	WriteData(0x12);
	WriteData(0x14);
	WriteData(0x17);

	WriteCommand(0XE1); /* Set Gamma */
	WriteData(0xd0);
	WriteData(0x00);
	WriteData(0x02);
	WriteData(0x07);
	WriteData(0x0a);
	WriteData(0x28);
	WriteData(0x31);
	WriteData(0x54);
	WriteData(0x47);
	WriteData(0x0e);
	WriteData(0x1c);
	WriteData(0x17);
	WriteData(0x1b);
	WriteData(0x1e);

	WriteCommand(0x2A);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0xef);

	WriteCommand(0x2B);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x01);
	WriteData(0x3f);

	// 执行这条后才真正开启显示，不再是那种除了背光什么都没有的状态。
	WriteCommand(0x29);
	Clear(Color::Black);
	TurnOnBackLight();
}

void bsp::ST7789LcdDriver::DisplayOff()
{
	WriteCommand(0X28);
}

void bsp::ST7789LcdDriver::SetScanDirection(bool horizontal_priority_scanning,
											bsp::ILcd::HorizontalDirection hdir,
											bsp::ILcd::VerticalDirection vdir)
{
	auto direction_code = [](bool horizontal_priority_scanning,
							 HorizontalDirection hdir,
							 VerticalDirection vdir)
	{
		if (horizontal_priority_scanning)
		{
			if (hdir == HorizontalDirection::LeftToRight && vdir == VerticalDirection::TopToBottom)
			{
				return 0b000 << 5;
			}
			else if (hdir == HorizontalDirection::LeftToRight && vdir == VerticalDirection::BottomToTop)
			{
				return 0b100 << 5;
			}
			else if (hdir == HorizontalDirection::RightToLeft && vdir == VerticalDirection::TopToBottom)
			{
				return 0b010 << 5;
			}
			else if (hdir == HorizontalDirection::RightToLeft && vdir == VerticalDirection::BottomToTop)
			{
				return 0b110 << 5;
			}
		}

		// 以下是垂直优先扫描
		if (hdir == HorizontalDirection::LeftToRight && vdir == VerticalDirection::TopToBottom)
		{
			return 0b001 << 5;
		}
		else if (hdir == HorizontalDirection::LeftToRight && vdir == VerticalDirection::BottomToTop)
		{
			return 0b101 << 5;
		}
		else if (hdir == HorizontalDirection::RightToLeft && vdir == VerticalDirection::TopToBottom)
		{
			return 0b011 << 5;
		}

		// hdir == HorizontalDirection::RightToLeft && vdir == VerticalDirection::BottomToTop
		return 0b111 << 5;
	};

	_is_horizontal_priority_scanning = horizontal_priority_scanning;
	_horizontal_direction = hdir;
	_vertical_direction = vdir;
	WriteCommand(0X36,
				 direction_code(horizontal_priority_scanning, hdir, vdir) | 0x8);

	SetWindow(0, 0, Width(), Height());
}

void bsp::ST7789LcdDriver::Clear(Color color)
{
	SetWindow(0, 0, Width(), Height());
	SerCursor(0, 0);
	PrepareForRendering();
	for (uint32_t i = 0; i < PointCount(); i++)
	{
		WriteData(ColorCode(color));
	}
}

uint32_t bsp::ST7789LcdDriver::Width()
{
	if (_is_horizontal_priority_scanning)
	{
		// 如果是水平优先扫描，则屏幕当前宽度就是原始宽度
		return OriginalWidth();
	}

	// 否则将原始高度作为屏幕当前实际宽度
	return OriginHeight();
}

uint32_t bsp::ST7789LcdDriver::Height()
{
	if (_is_horizontal_priority_scanning)
	{
		// 如果是水平优先扫描，则将屏幕原始高度作为当前实际高度
		return OriginHeight();
	}

	// 否则将屏幕原始宽度作为当前实际高度。
	return OriginalWidth();
}

void bsp::ST7789LcdDriver::PrepareForRendering()
{
	// 写入此命令后才可以开始写像素
	WriteCommand(0X2C);
}

void bsp::ST7789LcdDriver::SetWindow(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	WriteCommand(0X2A);
	WriteData(x >> 8);
	WriteData(x & 0xff);
	WriteData((x + width - 1) >> 8);
	WriteData((x + width - 1) & 0XFF);
	WriteCommand(0X2B);
	WriteData(y >> 8);
	WriteData(y & 0xff);
	WriteData((y + height - 1) >> 8);
	WriteData((y + height - 1) & 0XFF);
}

void bsp::ST7789LcdDriver::SerCursor(uint32_t x, uint32_t y)
{
	WriteCommand(0X2A);
	WriteData(x >> 8);
	WriteData(x & 0XFF);
	WriteCommand(0X2B);
	WriteData(y >> 8);
	WriteData(y & 0XFF);
}

void bsp::ST7789LcdDriver::DrawPoint(uint32_t x, uint32_t y, uint16_t rgb_565)
{
	SerCursor(x, y);
	PrepareForRendering();
	WriteData(rgb_565);
}

#pragma endregion
