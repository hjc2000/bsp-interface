#pragma once
#include <stdint.h>

namespace bsp
{
	class IPhyController
	{
	public:
		/// @brief 读 PHY 的寄存器
		/// @param register_index 寄存器索引。
		/// @return
		virtual uint32_t ReadRegister(uint32_t register_index) = 0;

		/// @brief 写 PHY 的寄存器。
		/// @param register_index 寄存器索引。
		/// @param value
		virtual void WriteRegister(uint32_t register_index, uint32_t value) = 0;

		/// @brief 通过 PHY 的复位引脚将 PHY 复位。
		virtual void HardwareReset() = 0;
	};
} // namespace bsp
