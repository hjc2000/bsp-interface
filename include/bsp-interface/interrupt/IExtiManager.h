#pragma once
#include <functional>
#include <stdint.h>

namespace bsp
{
	/// @brief 外部中断管理器
	class IExtiManager
	{
	public:
		virtual ~IExtiManager() = default;

		/// @brief 注册使用一条外部中断线。
		/// @param line_id 中断线的 id
		/// @param callback 发生中断时的回调函数
		virtual void Register(int line_id, std::function<void()> callback) = 0;

		/// @brief 注销一条外部中断线的使用。
		/// @param line_id 中断线的 id
		virtual void Unregister(int line_id) = 0;
	};
}
