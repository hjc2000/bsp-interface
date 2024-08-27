#pragma once
#include <bsp-interface/interrupt/IExtiManager.h>
#include <bsp-interface/interrupt/IInterruptSwitch.h>
#include <bsp-interface/interrupt/IsrManager.h>

bsp::IInterruptSwitch &DI_InterruptSwitch();

/// @brief 中断管理器。
/// @note 此依赖本库已经提供了，不需要实现此函数了。
/// @return
bsp::IsrManager &DI_IsrManager();

/// @brief 外部中断管理器。
/// @return
bsp::IExtiManager &DI_ExtiManager();
