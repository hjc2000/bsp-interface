#pragma once
#include <base/container/ICollection.h>
#include <bsp-interface/IDelayer.h>
#include <bsp-interface/ISysTick.h>

/// @brief 复位单片机
void DI_Reset();

#pragma region 时钟
bsp::ISysTick &DI_SysTick();
bsp::IDelayer &DI_Delayer();

#pragma endregion
