#pragma once

namespace bsp
{
	/// @brief 引脚工作模式。
	enum class GpioPinWorkMode
	{
		/// @brief 输入
		Input,

		/// @brief 输入中断模式。上升沿触发。
		InputInterruptRisingEdgeTrigger,

		/// @brief 输入中断模式。下降沿触发。
		InputInterruptFallingEdgeTrigger,

		/// @brief 输入中断模式。上升沿和下降沿都可触发。
		InputInterruptBothEdgeTrigger,

		/// @brief 推挽输出
		OutputPushPull,

		/// @brief 开漏输出
		OutputOpenDrain,

		/// @brief 复用功能
		AlternateFunction,
	};
}