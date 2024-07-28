#pragma once
#include <map>
#include <string>

namespace bsp
{
	/// @brief GPIO 管理器。
	///
	/// @note 这里只有引脚，没有端口的概念。对于像 stm32 这种分为 port 和 pin 的型号，可以使用
	/// 	pin_id = port_index * 16 + pin_index
	/// 这种引脚 id 映射方式。
	///
	/// @example 例如 PORTB 的 pin1 的 id 的计算过程如下：
	/// 	@li 每个端口有 16 个引脚
	/// 	@li PORTB 是第 2 个端口，索引号是 1，因为索引号从 0 开始。
	/// 	@li pin1 是第 2 个引脚，索引号是 1，因为索引号从 0 开始。
	/// 则
	/// 	pin_id = 1 * 16 + 1 = 17
	///
	/// @example PORTB 的 pin0 则是
	/// 	pin_id = 1 * 16 + 0 =16
	/// 以此类推。
	class IGpioManager
	{
	public:
		/// @brief 初始化引脚。
		/// @param pin_id 引脚 ID。
		/// @param pin_mode 引脚模式。
		/// @param pin_pull 引脚上下拉模式。例如可以选择：上拉，下拉，悬空。
		/// @param ex_options 额外的选项，使用 map，键为字符串，值为 int，不同平台应该编写一份
		/// 文档，详细说明可选的字符串和每个字符串对应的可选值。
		virtual void InitializePin(int pin_id,
								   int pin_mode,
								   int pin_pull,
								   std::map<std::string, int> *ex_options = nullptr) = 0;

		virtual void DigitalWritePin(int pin_id, bool value) = 0;
		virtual bool DigitalReadPin(int pin_id) = 0;
	};
}
