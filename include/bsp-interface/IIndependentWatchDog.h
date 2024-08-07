#pragma once
#include <chrono>

namespace bsp
{
	/// @brief 独立看门狗接口。
	class IIndependentWatchDog
	{
	public:
		virtual ~IIndependentWatchDog() = default;

		/// @brief 看门狗超时时间。
		/// @return
		virtual std::chrono::milliseconds WatchDogTimeoutDuration() const = 0;

		/// @brief 设置看门狗超时时间。
		/// @note 如果设置的毫秒数超出了能力范围，则会使用能达到的最大计时时间。
		/// @param value
		virtual void SetWatchDogTimeoutDuration(std::chrono::milliseconds value) = 0;

		/// @brief 喂狗
		virtual void Feed() = 0;
	};
}
