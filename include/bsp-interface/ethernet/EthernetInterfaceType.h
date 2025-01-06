#pragma once

namespace bsp
{
	/// @brief 以太网控制器连接着 PHY 的接口类型。
	enum class EthernetInterfaceType
	{
		/// @brief 独立介质接口。
		MII,

		/// @brief 精简独立介质接口。
		RMII,
	};
} // namespace bsp
