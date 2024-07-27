#pragma once
#include <bsp-interface/IDelayer.h>
#include <bsp-interface/ISysTick.h>
#include <bsp-interface/interrupt/IInterruptSwitch.h>
#include <bsp-interface/interrupt/IsrManager.h>
#include <bsp-interface/key/IKeyScanner.h>

bsp::ISysTick &DI_SysTick();
bsp::IDelayer &DI_Delayer();
bsp::IInterruptSwitch &DI_InterruptSwitch();

/// @brief 中断管理器。
/// @return
bsp::IsrManager &DI_IsrManager();

bsp::IKeyScanner &DI_KeyScanner();
