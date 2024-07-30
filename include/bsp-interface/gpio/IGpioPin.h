#pragma once
#include <functional>
#include <string>

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

	/// @brief 引脚上下拉模式。
	enum GpioPullMode
	{
		NoPull,
		PullUp,
		PullDown,
	};

	/// @brief 管理单个 GPIO 引脚。
	class IGpioPin
	{
	public:
		/// @brief 引脚名称
		/// @return
		virtual std::string const &PinName() const = 0;

#pragma region 属性
		/// @brief 引脚工作模式。
		/// @return
		virtual GpioPinWorkMode WorkMode() const = 0;
		virtual void SetWorkMode(GpioPinWorkMode value) = 0;

		/// @brief 引脚上下拉模式。
		/// @return
		virtual GpioPullMode PullMode() const = 0;
		virtual void SetPullMode(GpioPullMode value) = 0;

		/// @brief 引脚速度等级。
		/// @note 有的平台引脚支持设置速度等级。
		/// @return
		virtual int SpeedLevel() const = 0;
		virtual void SetSpeedLevel(int value) = 0;
#pragma endregion

		virtual void Open() = 0;
		virtual void Close() = 0;

		virtual bool ReadPin() = 0;
		virtual void WritePin(bool value) = 0;

		/// @brief 设置中断回调函数
		/// @warning 只有当前引脚处于关闭状态才能设置。
		/// @param callback
		virtual void SetInterruptCallback(std::function<void()> callback) = 0;
	};
}
