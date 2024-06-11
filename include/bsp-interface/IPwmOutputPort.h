#pragma once
#include<base/math/Fraction.h>
#include<chrono>

namespace bsp
{
	class IPwmOutputPort
	{
	public:
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