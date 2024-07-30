#pragma once
#include <base/container/IEnumerable.h>
#include <bsp-interface/gpio/GpioPinWorkMode.h>
#include <bsp-interface/gpio/GpioPullMode.h>
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
		virtual GpioPullMode PullMode() const = 0;
		virtual void SetPullMode(GpioPullMode value) = 0;

		/// @brief 引脚速度等级。
		/// @note 有的平台引脚支持设置速度等级。不支持的平台忽略就好。
		/// @return
		virtual int SpeedLevel() const = 0;
		virtual void SetSpeedLevel(int value) = 0;

		/// @brief 复用功能。
		/// @return
		virtual std::string AlternateFunction() const = 0;
		virtual void SetAlternateFunction(std::string value) = 0;
#pragma endregion

		/// @brief 支持的复用功能。
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
