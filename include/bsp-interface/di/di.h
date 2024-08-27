#pragma once
#include <base/container/ICollection.h>
#include <bsp-interface/IDelayer.h>
#include <bsp-interface/interrupt/IExtiManager.h>
#include <bsp-interface/interrupt/IInterruptSwitch.h>
#include <bsp-interface/interrupt/IsrManager.h>
#include <bsp-interface/ISysTick.h>

/// @brief 复位单片机
void DI_Reset();

#pragma region 时钟
bsp::ISysTick &DI_SysTick();
bsp::IDelayer &DI_Delayer();

#pragma endregion

#pragma region 中断
bsp::IInterruptSwitch &DI_InterruptSwitch();

/// @brief 中断管理器。
/// @note 此依赖本库已经提供了，不需要实现此函数了。
/// @return
bsp::IsrManager &DI_IsrManager();

/// @brief 外部中断管理器。
/// @return
bsp::IExtiManager &DI_ExtiManager();
#pragma endregion
