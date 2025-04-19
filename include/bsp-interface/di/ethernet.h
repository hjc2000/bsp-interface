#pragma once
#include <bsp-interface/ethernet/IEthernetPort.h>

namespace bsp
{
	namespace di
	{
		namespace ethernet
		{
			/// @brief 以太网端口。
			/// @note 负责 PHY 的人，利用 DI_EthernetController 抽象出来的单片机的以太网控制器来操作 PHY，
			/// 实现本函数。
			/// @return
			bsp::IEthernetPort &EthernetPort();
		} // namespace ethernet
	} // namespace di
} // namespace bsp
