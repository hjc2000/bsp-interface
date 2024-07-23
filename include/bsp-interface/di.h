#pragma once
#include <bsp-interface/IDelayer.h>
#include <bsp-interface/ISysTick.h>

bsp::ISysTick &DI_SysTick();
bsp::IDelayer &DI_Delayer();
