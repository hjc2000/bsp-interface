#pragma once
#include <bsp-interface/ethernet/IEthernetController.h>
#include <bsp-interface/ethernet/IEthernetPort.h>

/// @brief 以太网控制器。
/// @return
bsp::IEthernetController &DI_EthernetController();

/// @brief 以太网端口。
/// @return
bsp::IEthernetPort &DI_EthernetPort();
