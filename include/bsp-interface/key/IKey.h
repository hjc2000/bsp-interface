#pragma once
#include <bitset>
#include <chrono>

namespace bsp
{
	/// @brief 按键接口。
	class IKey
	{
	public:
		/// @brief 按键处于被按下的状态。
		/// @note 此函数内部不会进行按键消抖，抖动会引起此函数返回值的变化。
		/// @return 按键处于被按下的状态则返回 true，按键不处于被按下的状态则返回 false。
		virtual bool KeyIsDown() = 0;

		/// @brief 按键处于松开的状态。
		/// @return 处于松开的状态返回 true，不处于松开的状态返回 false。
		bool KeyIsUp()
		{
			return !KeyIsDown();
		}
	};
}
