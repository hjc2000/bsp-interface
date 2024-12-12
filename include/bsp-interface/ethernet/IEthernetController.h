#pragma once
#include <base/net/Mac.h>
#include <string>

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
        /// @brief 以太网控制器的名称。
        /// @return
        virtual std::string Name() const = 0;

        /// @brief 打开以太网控制器。
        /// @param interface_type 连接着 PHY 的接口类型。（使用的是 MII 还是 RMII）
        /// @param phy_address PHY 的地址。
        /// @param mac MAC 地址。
        virtual void Open(bsp::IEthernetController_InterfaceType interface_type,
                          uint32_t phy_address,
                          base::Mac const &mac) = 0;

        /// @brief 获取本控制器当前使用的接口类型。
        /// @note 要打开本控制器后本属性才有效。
        /// @return
        virtual bsp::IEthernetController_InterfaceType InterfaceType() const = 0;

        /// @brief 获取本控制器绑定的 PHY 地址。
        /// @note 要打开本控制器后本属性才有效。
        /// @return
        virtual uint32_t PhyAddress() const = 0;

        /// @brief 获取本控制器绑定的 MAC 地址。
        /// @note 要打开本控制器后本属性才有效。
        /// @return
        virtual base::Mac Mac() const = 0;

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
