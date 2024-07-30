#pragma once
#include <base/container/IEnumerable.h>
#include <bsp-interface/gpio/GpioPinPullMode.h>
#include <bsp-interface/gpio/GpioPinWorkMode.h>
#include <functional>
#include <string>

namespace bsp
{
	/// @brief 管理单个 GPIO 引脚。
	class IGpioPin
	{
	public:
		/// @brief 引脚名称
		/// @return
		virtual std::string PinName() const = 0;

		/// @brief 端口索引。
		/// @note 例如 stm32 的 PB0 的端口索引为 1.
		/// @return
		virtual int PortIndex() = 0;

		/// @brief 引脚索引。
		/// @note 例如 stm32 的 PB0 的引脚索引为 0.
		/// @return
		virtual int PinIndex() = 0;

#pragma region 属性
		/// @brief 指示此引脚是否已经打开。
		/// @return
		virtual bool IsOpen() = 0;

		/// @brief 引脚工作模式。
		/// @return
		virtual GpioPinWorkMode WorkMode() const = 0;
		virtual void SetWorkMode(GpioPinWorkMode value) = 0;

		/// @brief 引脚上下拉模式。
		/// @return
		virtual GpioPinPullMode PullMode() const = 0;
		virtual void SetPullMode(GpioPinPullMode value) = 0;

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
#pragma endregion

		/// @brief 支持的复用功能。
		/// @note 复用功能是非常复杂的，各个型号单片机都不一样，所以采用字符串。
		/// @note 假设某个单片机的一个引脚的复用功能有：uart1, timer1_compare_output 等。
		/// 这种名称是与具体型号高度相关的，所以本库无法提供一个枚举来列举这些情况。
		/// @return
		virtual base::IEnumerable<std::string> SupportedAlternateFunctions() = 0;

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
