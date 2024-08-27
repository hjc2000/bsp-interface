#pragma once
#include <base/container/ICollection.h>
#include <bsp-interface/ISysTick.h>

/// @brief 复位单片机
void DI_Reset();

bsp::ISysTick &DI_SysTick();
