#pragma once
#include <string>

namespace bsp
{
	/// @brief 引脚工作模式。
	enum class IGpioPinWorkMode
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

	/// @brief 引脚上下拉模式。
	enum class IGpioPinPullMode
	{
		NoPull,
		PullUp,
		PullDown,
	};

	/// @brief GPIO 引脚选项
	class IGpioPinOptions
	{
	public:
		/// @brief 引脚工作模式。
		/// @return
		virtual bsp::IGpioPinWorkMode WorkMode() const = 0;
		virtual void SetWorkMode(bsp::IGpioPinWorkMode value) = 0;

		/// @brief 引脚上下拉模式。
		/// @return
		virtual bsp::IGpioPinPullMode PullMode() const = 0;
		virtual void SetPullMode(bsp::IGpioPinPullMode value) = 0;

		/// @brief 引脚速度等级。
		/// @note 有的平台引脚支持设置速度等级。不支持的平台忽略就好。
		/// @return
		virtual int SpeedLevel() const = 0;
		virtual void SetSpeedLevel(int value) = 0;

		/// @brief 复用功能。
		/// @return
		virtual std::string AlternateFunction() const = 0;

		/// @brief 设置复用功能。
		/// @note 复用功能是非常复杂的，各个型号单片机都不一样，所以采用字符串。
		/// @note 假设某个单片机的一个引脚的复用功能有：uart1, timer1_compare_output 等。
		/// 这种名称是与具体型号高度相关的，所以本库无法提供一个枚举来列举这些情况。
		/// @param value
		virtual void SetAlternateFunction(std::string value) = 0;
	};
}
