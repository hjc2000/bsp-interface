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
		/// <summary>
		///		支持的最小周期。设置周期时不能小于此值。
		/// </summary>
		/// <returns></returns>
		virtual std::chrono::microseconds MinPeriod() = 0;

		/// <summary>
		///		支持的最大周期。设置周期时不能大于此值。
		/// </summary>
		/// <returns></returns>
		virtual std::chrono::microseconds MaxPeriod() = 0;

		/// <summary>
		///		周期
		/// </summary>
		/// <returns></returns>
		virtual std::chrono::microseconds Period() const = 0;
		virtual void SetPeriod(std::chrono::microseconds value) = 0;

		/// <summary>
		///		占空比
		/// </summary>
		/// <returns></returns>
		virtual base::Fraction Pulse() const = 0;
		virtual void SetPulse(base::Fraction value) = 0;

		/// <summary>
		///		启动 PWM 输出
		/// </summary>
		virtual void Start() = 0;
	};
}