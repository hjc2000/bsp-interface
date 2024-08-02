#pragma once
#include <string>

namespace bsp
{
#pragma region 枚举
	/// @brief 引脚方向
	enum class IGpioPinDirection
	{
		/// @brief 输入
		Input,

		/// @brief 输出
		Output,

		/// @brief 双向
		TwoWay,

		/// @brief 高阻态。
		HighResistanceState,
	};

	/// @brief 引脚工作模式。
	enum class IGpioPinWorkMode
	{
		/// @brief 通用输入输出功能。
		Gpio,

		/// @brief 事件功能。
		Event,

		/// @brief 模拟量功能。
		Analog,

		/// @brief 复用功能。
		AlternateFunction,
	};

	/// @brief 触发边沿。
	enum class IGpioPinTriggerEdge
	{
		/// @brief 禁用中断
		Disable,

		/// @brief 上升沿
		RisingEdge,

		/// @brief 下降沿
		FallingEdge,

		/// @brief 双边沿
		BothEdge,
	};

	/// @brief 引脚上下拉模式。
	enum class IGpioPinPullMode
	{
		/// @brief 不拉
		NoPull,

		/// @brief 上拉
		PullUp,

		/// @brief 下拉
		PullDown,
	};

	/// @brief 引脚驱动模式。
	/// @note 引脚方向为输出时才有效。
	enum class IGpioPinDriver
	{
		PushPull,
		OpenDrain,
	};
#pragma endregion

	/// @brief GPIO 引脚选项
	class IGpioPinOptions
	{
	public:
		/// @brief 方向。
		/// @return
		virtual bsp::IGpioPinDirection Direction() const = 0;
		virtual void SetDirection(bsp::IGpioPinDirection value) = 0;

		/// @brief 引脚工作模式。
		/// @return
		virtual bsp::IGpioPinWorkMode WorkMode() const = 0;
		virtual void SetWorkMode(bsp::IGpioPinWorkMode value) = 0;

		/// @brief 触发边沿。
		/// @return
		virtual bsp::IGpioPinTriggerEdge TriggerEdge() const = 0;
		virtual void SetTriggerEdge(bsp::IGpioPinTriggerEdge value) = 0;

		/// @brief 引脚上下拉模式。
		/// @return
		virtual bsp::IGpioPinPullMode PullMode() const = 0;
		virtual void SetPullMode(bsp::IGpioPinPullMode value) = 0;

		/// @brief 引脚驱动模式。
		/// @note 引脚方向为输出时才有效。
		/// @return
		virtual bsp::IGpioPinDriver Driver() const = 0;
		virtual void SetDriver(bsp::IGpioPinDriver value) = 0;

		/// @brief 引脚速度等级。等级越高速度越快。
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
