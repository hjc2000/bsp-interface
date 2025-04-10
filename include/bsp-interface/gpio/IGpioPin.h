#pragma once
#include <functional>
#include <string>

namespace bsp
{
	/* #region 打开引脚参数类 */

	///
	/// @brief 引脚方向
	///
	enum class IGpioPinDirection
	{
		///
		/// @brief 输入
		///
		Input,

		///
		/// @brief 输出
		///
		Output,

		///
		/// @brief 双向
		///
		TwoWay,

		///
		/// @brief 高阻态。
		///
		HighResistanceState,
	};

	///
	/// @brief 引脚工作模式。
	///
	enum class IGpioPinWorkMode
	{
		///
		/// @brief 通用输入输出功能。
		///
		Gpio,

		///
		/// @brief 事件功能。
		///
		Event,

		///
		/// @brief 模拟量功能。
		///
		Analog,

		///
		/// @brief 复用功能。
		///
		AlternateFunction,
	};

	///
	/// @brief 触发边沿。
	///
	enum class IGpioPinTriggerEdge
	{
		///
		/// @brief 禁用中断
		///
		Disable,

		///
		/// @brief 上升沿
		///
		RisingEdge,

		///
		/// @brief 下降沿
		///
		FallingEdge,

		///
		/// @brief 双边沿
		///
		BothEdge,
	};

	///
	/// @brief 引脚上下拉模式。
	///
	enum class IGpioPinPullMode
	{
		///
		/// @brief 不拉
		///
		NoPull,

		///
		/// @brief 上拉
		///
		PullUp,

		///
		/// @brief 下拉
		///
		PullDown,
	};

	///
	/// @brief 引脚驱动模式。
	/// @note 引脚方向为输出时才有效。
	///
	enum class IGpioPinDriver
	{
		PushPull,
		OpenDrain,
	};

	/* #endregion */

	namespace gpio
	{
		class gpio_handle;

		bool read_pin(bsp::gpio::gpio_handle &handle);

	} // namespace gpio

	///
	/// @brief 管理单个 GPIO 引脚。
	///
	class IGpioPin
	{
	public:
		///
		/// @brief 引脚名称
		/// @return
		///
		virtual std::string PinName() const = 0;

		///
		/// @brief 指示此引脚是否已经打开。
		///
		/// @return
		///
		virtual bool IsOpen() = 0;

		/* #region 打开 */

		///
		/// @brief 将引脚打开为输入模式。
		///
		/// @param pull_mode 拉模式。可以选择上拉、下拉、不拉。
		/// @param trigger_edge 中断触发边沿。
		///
		virtual void OpenAsInputMode(bsp::IGpioPinPullMode pull_mode,
									 bsp::IGpioPinTriggerEdge trigger_edge);

		///
		/// @brief 将引脚打开为输出模式。
		///
		/// @param pull_mode 拉模式。
		/// @param driver_mode 驱动模式。
		///
		virtual void OpenAsOutputMode(bsp::IGpioPinPullMode pull_mode,
									  bsp::IGpioPinDriver driver_mode);

		///
		/// @brief 将引脚打开为复用功能。
		///
		/// @param function_name 复用功能名称。
		/// @param pull_mode 拉模式。
		/// @param driver_mode 驱动模式。
		///
		virtual void OpenAsAlternateFunctionMode(std::string function_name,
												 bsp::IGpioPinPullMode pull_mode,
												 bsp::IGpioPinDriver driver_mode);
		/* #endregion */

		virtual void Close() = 0;

		virtual bool ReadPin() = 0;
		virtual void WritePin(bool value) = 0;
		virtual void TogglePin() = 0;

		///
		/// @brief 设置中断回调函数。
		///
		/// @warning 只有当前引脚处于关闭状态才能设置。
		///
		/// @param callback
		///
		virtual void RegisterInterruptCallback(std::function<void()> callback) = 0;

		///
		/// @brief 取消注册此引脚的中断回调函数。
		///
		virtual void UnregisterInterruptCallback() = 0;
	};
} // namespace bsp
