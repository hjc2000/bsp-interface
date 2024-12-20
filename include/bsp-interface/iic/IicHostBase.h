#pragma once
#include <bsp-interface/iic/IIicHost.h>

namespace bsp
{
	class IicHostBase :
		public bsp::IIicHost
	{
	public:
		/// @brief 如果传入的值比现有的 SCL 周期更大，则设置 SCL 的周期，否则不设置。
		/// @param value
		void SetSclCycleWhenGreater(std::chrono::microseconds value) override;

		/// @brief 设置等待从机的 ACK 信号的超时周期数。但是本方法只有在新的值比旧的值
		/// 更大时才会设置。
		/// 单位： SCL 的周期。
		/// @param value
		void SetWaitingForAckTimeoutCycleCountWhenGreater(int value) override;
	};
} // namespace bsp
