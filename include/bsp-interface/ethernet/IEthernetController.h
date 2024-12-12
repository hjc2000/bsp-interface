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
    /// @note 本类的目的是封装单片机中的以太网控制器。单片机外部可以选择的 PHY 芯片各种各样，每种
    /// PHY 芯片的操作方式，寄存器的定义都不一样。本来不关注 PHY 的这些区别，本类专注于封装以太网
    /// 控制器，所以仅仅定义了读 PHY 寄存器和写 PHY 寄存器这两个方法，不会定义 PHY 的寄存器的具体
    /// 操作。像配置速率、双工/半双工、自动协商、是否交叉...... 等，交给 IEthernetPort 去完成。
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
