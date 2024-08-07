#pragma once
#include <bsp-interface/IDelayer.h>
#include <bsp-interface/lcd/ILcd.h>

namespace bsp
{
	class ST7789LcdDriver
		: public bsp::ILcd
	{
	protected:
		ST7789LcdDriver(bsp::IDelayer &delayer)
			: _delayer(delayer)
		{
		}

	private:
		bsp::IDelayer &_delayer;
		bool _is_horizontal_priority_scanning = true;
		bsp::ILcd::HorizontalDirection _horizontal_direction = bsp::ILcd::HorizontalDirection::LeftToRight;
		bsp::ILcd::VerticalDirection _vertical_direction = bsp::ILcd::VerticalDirection::TopToBottom;

		/// @brief 屏幕初始宽度。与屏幕旋转无关，无论屏幕怎么旋转，本属性都保持不变。
		/// @return
		static consteval uint32_t OriginalWidth()
		{
			return 240;
		}

		/// @brief 屏幕初始高度。与屏幕旋转无关，无论屏幕怎么旋转，本属性都保持不变。
		/// @return
		static consteval uint32_t OriginHeight()
		{
			return 320;
		}

		/// @brief 屏幕总共有多少个点。
		/// @return
		static consteval uint32_t PointCount()
		{
			return OriginalWidth() * OriginHeight();
		}

		uint16_t ColorCode(bsp::Color color)
		{
			switch (color)
			{
			case bsp::Color::Red:
			{
				return 0x001F;
			}
			case bsp::Color::Green:
			{
				return 0x07E0;
			}
			case bsp::Color::Blue:
			{
				return 0xF800;
			}
			case bsp::Color::White:
			{
				// 0xffff 表示该像素的 3 个液晶全部透光度开到最大，呈现出白色
				return UINT16_MAX;
			}
			case bsp::Color::Black:
			default:
			{
				// 0 表示全不透光，所以是黑色
				return 0;
			}
			}
		}

#pragma region 接口
	public:
		virtual void WriteCommand(uint16_t cmd) = 0;
		virtual void WriteCommand(uint16_t cmd, uint16_t param) = 0;

		virtual void WriteData(uint16_t data) = 0;
		virtual uint16_t ReadData() = 0;

		virtual void TurnOnBackLight() = 0;
		virtual void TurnOffBackLight() = 0;
#pragma endregion

#pragma region ILcd
	public:
		uint32_t LcdDriverChipId() override;

		void DisplayOn() override;
		void DisplayOff() override;

		/// @brief 设置扫描方向。
		/// @note 让 LCD 显示的方法是将屏幕上的一个个像素的 RGB 值逐个写入。
		/// 有多少个像素，就要写入多少组 RGB 值。写入一个像素的 RGB 值后，
		/// 驱动芯片会自动将位置指针递增，下次写入 RGB 就是对应下一个像素了。
		/// 驱动芯片内部自动递增的指针就是扫描指针，指向的是当前要被写入的像素。
		/// 扫描顺序可以是先水平，后竖直，也可以是先竖直，后水平。水平又可以分为
		/// 从左到右和从右到左。竖直可以分为从上到下和从下到上。
		///
		/// @param horizontal_priority_scanning
		/// @param hdir
		/// @param vdir
		void SetScanDirection(bool horizontal_priority_scanning,
							  bsp::ILcd::HorizontalDirection hdir,
							  bsp::ILcd::VerticalDirection vdir) override;

		void Clear(Color color) override;

		uint32_t Width() override;
		uint32_t Height() override;

		/// @brief 每次向屏幕中写像素前都需要调用一次本函数，然后就可以连续写入像素了。
		/// @note 推测本函数的作用是让 LCD 驱动芯片内部的一个指针复位，这样写入像素
		/// 后才能从原点开始填充。或者之前用了其他命令将驱动芯片置于非写入像素的模式下，
		/// 此时必须调用本函数才能让驱动芯片回到写入像素的模式。
		void PrepareForRendering();

		void SetWindow(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		void SerCursor(uint32_t x, uint32_t y) override;

		void DrawPoint(uint32_t x, uint32_t y, uint16_t rgb_565) override;
#pragma endregion
	};
}
