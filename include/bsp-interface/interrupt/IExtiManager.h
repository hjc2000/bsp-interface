#pragma once
#include <functional>
#include <stdint.h>

namespace bsp
{
	/// @brief 外部中断管理器
	class IExtiManager
	{
	public:
		/// @brief 注册使用一条外部中断线。
		/// @param line_index
		/// @param callback 发生中断时的回调函数
		virtual void Register(int line_index, std::function<void()> callback) = 0;

		/// @brief 注销一条外部中断线的使用。
		/// @param line_index
		virtual void Unregister(int line_index) = 0;
	};
}
