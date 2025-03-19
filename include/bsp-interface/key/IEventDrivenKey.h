#pragma once

namespace bsp
{
	/// @brief 事件驱动的按钮。
	/// @note 由外部事件驱动，设置标志位来表示按键被按下了。这里只提供读取标志的方法。
	class IEventDrivenKey
	{
	public:
		virtual ~IEventDrivenKey() = default;

		virtual bool IsPressed() = 0;
		virtual void ClearPressedFlag() = 0;
	};
} // namespace bsp
