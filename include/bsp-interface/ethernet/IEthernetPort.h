#pragma once
#include <base/unit/Bps.h>
#include <bsp-interface/ethernet/IEthernetController.h>

namespace bsp
{
    /// @brief 以太网端口。
    /// @note 端口就是以太网控制器 + PHY 芯片。
    class IEthernetPort
    {
    public:
        /// @brief 读 PHY 的寄存器
        /// @param register_index 寄存器索引。
        /// @return
        virtual uint32_t ReadPHYRegister(uint32_t register_index) = 0;

        /// @brief 写 PHY 的寄存器。
        /// @param register_index 寄存器索引。
        /// @param value
        virtual void WritePHYRegister(uint32_t register_index, uint32_t value) = 0;
    };
} // namespace bsp
