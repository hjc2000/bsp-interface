#pragma once
#include <base/net/Mac.h>
#include <base/unit/Bps.h>

namespace bsp
{
#pragma region 参数类
    /// @brief 以太网控制器连接着 PHY 的接口类型。
    enum class IEthernetController_InterfaceType
    {
        /// @brief 独立介质接口。
        MII,

        /// @brief 精简独立介质接口。
        RMII,
    };
#pragma endregion

    /// @brief 以太网控制器接口。
    /// @note 以太网控制器使用 MII（独立介质接口）或 RMII（精简独立介质接口）控制外部的 PHY 芯片。
    class IEthernetController
    {
    public:
        /// @brief 打开以太网控制器。
        /// @param interface_type 连接着 PHY 的接口类型。（使用的是 MII 还是 RMII）
        /// @param mac MAC 地址。
        virtual void Open(bsp::IEthernetController_InterfaceType interface_type,
                          base::Mac const &mac) = 0;

        /// @brief 读 PHY 的寄存器
        ///
        /// @param phy_address PHY 的地址。
        /// @note 独立介质接口可以管理多个 PHY，每个 PHY 有自己的地址。
        ///
        /// @param register_index 寄存器索引。
        /// @return
        virtual uint32_t ReadPHYRegister(uint32_t phy_address, uint32_t register_index) = 0;

        /// @brief 写 PHY 的寄存器。
        ///
        /// @param phy_address PHY 的地址。
        /// @note 独立介质接口可以管理多个 PHY，每个 PHY 有自己的地址。
        ///
        /// @param register_index 寄存器索引。
        /// @param value
        virtual void WritePHYRegister(uint32_t phy_address, uint32_t register_index, uint32_t value) = 0;

        /// @brief 获取此接口的连接速率。
        /// @return
        virtual base::Bps Bitrate() = 0;
    };
} // namespace bsp
