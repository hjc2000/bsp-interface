#pragma once
#include<bsp-interface/lcd/ILcd.h>

namespace bsp
{
	class ST7789LcdDriver :
		public bsp::ILcd
	{
		#pragma region 接口
	public:
		virtual void WriteCommand(uint16_t cmd) = 0;
		virtual void WriteCommand(uint16_t cmd, uint16_t param) = 0;

		virtual void WriteData(uint16_t data) = 0;
		virtual uint16_t ReadData() = 0;

		virtual void TurnOnBackLight() = 0;
		virtual void TurnOffBackLight() = 0;
		#pragma endregion

	public:
		uint32_t LcdDriverChipId() override;

		void DisplayOn() override;
		void DisplayOff() override;

		void SetScanDirection(
			bool horizontal_priority_scanning,
			bsp::ILcd::HorizontalDirection hdir,
			bsp::ILcd::VerticalDirection vdir
		) override;

		void Clear(Color color) override;

		uint32_t Width() override;
		uint32_t Height() override;

		/// <summary>
		///		每次向屏幕中写像素前都需要调用一次本函数，然后就可以连续写入像素了。
		///		* 推测本函数的作用是让 LCD 驱动芯片内部的一个指针复位，这样写入像素
		///		  后才能从原点开始填充。或者之前用了其他命令将驱动芯片置于非写入像素的
		///		  模式下，此时必须调用本函数才能让驱动芯片回到写入像素的模式。
		/// </summary>
		void PrepareForRendering();

		void SetWindow(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		void SerCursor(uint32_t x, uint32_t y) override;

		void DrawPoint(uint32_t x, uint32_t y, uint16_t rgb_565) override;
	};
}