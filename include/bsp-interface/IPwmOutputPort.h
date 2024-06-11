#pragma once
#include<base/math/Fraction.h>
#include<chrono>

namespace bsp
{
	/// <summary>
	///		PWM 输出端口
	/// </summary>
	class IPwmOutputPort
	{
	public:
		#pragma region 周期
		/// <summary>
		///		支持的最小周期。设置周期时不能小于此值。
		/// </summary>
		/// <returns></returns>
		virtual std::chrono::microseconds MinPeriod() const = 0;

		/// <summary>
		///		支持的最大周期。设置周期时不能大于此值。
		/// </summary>
		/// <returns></returns>
		virtual std::chrono::microseconds MaxPeriod() const = 0;

		/// <summary>
		///		获取周期。
		/// </summary>
		/// <returns></returns>
		virtual std::chrono::microseconds Period() const = 0;

		/// <summary>
		///		设置周期。
		///		* 范围必须在 [MinPeriod, MaxPeriod] 上。
		///		* PWM 启动后可以通过此函数动态修改 PWM 周期。
		/// </summary>
		/// <param name="value"></param>
		virtual void SetPeriod(std::chrono::microseconds value) = 0;
		#pragma endregion

		/// <summary>
		///		占空比。
		///		* PWM 启动后可以通过此函数动态修改 PWM 占空比。
		/// </summary>
		/// <returns></returns>
		virtual base::Fraction Pulse() const = 0;
		virtual void SetPulse(base::Fraction value) = 0;

		/// <summary>
		///		启动 PWM 输出。
		/// </summary>
		virtual void Start() = 0;
	};
}