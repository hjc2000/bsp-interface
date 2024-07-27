#pragma once
#include <base/container/ICollection.h>
#include <bsp-interface/IDelayer.h>
#include <bsp-interface/IDigitalLed.h>
#include <bsp-interface/IIndependentWatchDog.h>
#include <bsp-interface/ISysTick.h>
#include <bsp-interface/interrupt/IInterruptSwitch.h>
#include <bsp-interface/interrupt/IsrManager.h>
#include <bsp-interface/key/IKeyScanner.h>
#include <bsp-interface/lcd/ILcd.h>

/// @brief 复位单片机
void DI_Reset();

bsp::ISysTick &DI_SysTick();
bsp::IDelayer &DI_Delayer();
bsp::IInterruptSwitch &DI_InterruptSwitch();

/// @brief 中断管理器。
/// @note 此依赖本库已经提供了，不需要实现此函数了。
/// @return
bsp::IsrManager &DI_IsrManager();

/// @brief 按键集合。
/// @return
base::IReadOnlyCollection<int, bsp::IKey *> &DI_KeyCollection();
bsp::IKeyScanner &DI_KeyScanner();

/// @brief 数字 LED 灯集合。
/// @return
base::IReadOnlyCollection<int, bsp::IDigitalLed *> &DI_DigitalLedCollection();

#pragma region 具体颜色的 LED
/* 具体颜色的 LED。有就实现，没有就不实现，也不要使用，避免发生链接错误。 */

bsp::IDigitalLed &DI_RedDigitalLed();
bsp::IDigitalLed &DI_GreenDigitalLed();
bsp::IDigitalLed &DI_BlueDigitalLed();
#pragma endregion

bsp::ILcd &DI_Lcd();

/// @brief 独立看门狗。
/// @return
bsp::IIndependentWatchDog &DI_IndependentWatchDog();
