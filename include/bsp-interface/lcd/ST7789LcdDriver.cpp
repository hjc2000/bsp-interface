#include"ST7789LcdDriver.h"

using namespace bsp;

void bsp::ST7789LcdDriver::TurnOnBackLight()
{
}

void bsp::ST7789LcdDriver::TurnOffBackLight()
{
}

uint32_t bsp::ST7789LcdDriver::LcdDriverChipId()
{
	return 0;
}

void bsp::ST7789LcdDriver::DisplayOn()
{
}

void bsp::ST7789LcdDriver::DisplayOff()
{
}

void bsp::ST7789LcdDriver::SetScanDirection(
	bool horizontal_priority_scanning,
	bsp::ILcd::HorizontalDirection hdir,
	bsp::ILcd::VerticalDirection vdir
)
{
}

void bsp::ST7789LcdDriver::Clear(Color color)
{
}

uint32_t bsp::ST7789LcdDriver::Width()
{
	return 0;
}

uint32_t bsp::ST7789LcdDriver::Height()
{
	return 0;
}

void bsp::ST7789LcdDriver::PrepareForRendering()
{
	// 写入此命令后才可以开始写像素
	WriteCommand(0X2C);
}

void bsp::ST7789LcdDriver::SetWindow(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
}

void bsp::ST7789LcdDriver::SerCursor(uint32_t x, uint32_t y)
{
}

void bsp::ST7789LcdDriver::DrawPoint(uint32_t x, uint32_t y, uint16_t rgb_565)
{
}
