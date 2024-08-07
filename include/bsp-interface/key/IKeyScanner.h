#pragma once
#include <bsp-interface/key/IKey.h>
#include <stdint.h>

namespace bsp
{
	/// @brief 按键扫描器接口
	class IKeyScanner
	{
	public:
		virtual ~IKeyScanner() = default;

		/// @brief 执行键盘扫描，更新内部状态。此函数应该被不断调用。
		/// @note 此函数需要被循环调用，这样才能扫描到按键事件。
		virtual void ScanKeys() = 0;

		/// @brief 检测指定的按键是否有按下动作事件
		/// @note 所谓按下动作，就是从松开变成按下的这个状态变化。本事件只有在这个边沿会触发一次。
		/// @note 在再次调用 ScanKeys 之前，本函数的返回值会保持一致。
		/// @param key_name
		/// @return 指定的按键有按键按下动作则返回 true，否则返回 false。
		virtual bool HasKeyDownEvent(std::string key_name) = 0;

		/// @brief 检测指定的按键是否有抬起动作事件。
		/// @note 所谓抬起动作，就是从按下变成松开的这个状态变化。本事件只有在这个边沿会触发一次。
		/// @note 在再次调用 ScanKeys 之前，本函数的返回值会保持一致。
		/// @param key_name
		/// @return 指定的按键有按键抬起动作则返回 true，否则返回 false。
		virtual bool HasKeyUpEvent(std::string key_name) = 0;

		/// @brief 检测指定的按键是否有被按压着事件。
		/// @note 所谓被按压着事件，就是最近一次调用 ScanKeys 得到的按键状态。即当前扫描的结果
		/// 是按键正被按着。
		/// @param key_name
		/// @return 指定的按键正被按着则返回 true，否则返回 false。
		virtual bool HasKeyPressedEvent(std::string key_name) = 0;
	};
}
