#pragma once
#include<bitset>
#include<chrono>

namespace bsp
{
	/// <summary>
	///		独立按键。
	///		- 所谓独立按键就是一个按键占用一个 GPIO 引脚。
	/// </summary>
	class IKey
	{
	public:
		/// <summary>
		///		按键处于被按下的状态。
		///		此函数内部不会进行按键消抖，抖动会引起此函数返回值的变化。
		/// </summary>
		/// <returns>按键处于被按下的状态则返回 true，按键不处于被按下的状态则返回 false。</returns>
		virtual bool KeyIsDown() = 0;

		bool KeyIsUp()
		{
			return !KeyIsDown();
		}
	};
}
