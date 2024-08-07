#pragma once
#include <chrono>
#include <functional>

namespace bsp
{
	class IBaseTimer
	{
	public:
		virtual ~IBaseTimer() = default;

		/// @brief 初始化定时器
		/// @param period 定时周期
		virtual void Initialize(std::chrono::milliseconds period) = 0;

		/// @brief 启动定时器。
		virtual void Start() = 0;

		/// @brief 停止定时器。
		virtual void Stop() = 0;

		/// @brief 设置定时时间到触发的回调。
		/// @note 设置为 nullptr 可以取消回调。
		/// @param func
		virtual void SetPeriodElapsedCallback(std::function<void()> func) = 0;
	};
}
