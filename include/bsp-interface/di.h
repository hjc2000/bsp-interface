#pragma once
#include <base/container/ICollection.h>
#include <bsp-interface/dma/IDmaChannel.h>
#include <bsp-interface/dma/IDmaOptions.h>
#include <bsp-interface/gpio/IGpioPin.h>
#include <bsp-interface/IDelayer.h>
#include <bsp-interface/IDigitalLed.h>
#include <bsp-interface/IIndependentWatchDog.h>
#include <bsp-interface/interrupt/IExtiManager.h>
#include <bsp-interface/interrupt/IInterruptSwitch.h>
#include <bsp-interface/interrupt/IsrManager.h>
#include <bsp-interface/ISysTick.h>
#include <bsp-interface/key/IKeyScanner.h>
#include <bsp-interface/lcd/ILcd.h>
#include <bsp-interface/serial/ISerial.h>

/// @brief 复位单片机
void DI_Reset();

#pragma region 时钟
bsp::ISysTick &DI_SysTick();
bsp::IDelayer &DI_Delayer();

/// @brief 独立看门狗。
/// @return
bsp::IIndependentWatchDog &DI_IndependentWatchDog();
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

#pragma region 按键
/// @brief 按键集合。
/// @return
base::IReadOnlyCollection<std::string, bsp::IKey *> &DI_KeyCollection();
bsp::IKeyScanner &DI_KeyScanner();
#pragma endregion

#pragma region LED
/// @brief 数字 LED 灯集合。
/// @return
base::IReadOnlyCollection<std::string, bsp::IDigitalLed *> &DI_DigitalLedCollection();

bsp::IDigitalLed &DI_RedDigitalLed();
bsp::IDigitalLed &DI_GreenDigitalLed();
bsp::IDigitalLed &DI_BlueDigitalLed();
#pragma endregion

#pragma region LCD
bsp::ILcd &DI_Lcd();
#pragma endregion

#pragma region GPIO
/// @brief 创建一个 GPIO 引脚的配置对象。
/// @return
std::shared_ptr<bsp::IGpioPinOptions> DICreate_GpioPinOptions();

/// @brief GPIO 引脚集合
/// @return
base::IReadOnlyCollection<std::string, bsp::IGpioPin *> &DI_GpioPinCollection();
#pragma endregion

#pragma region 串口
std::shared_ptr<bsp::ISerialOptions> DICreate_ISerialOptions();

/// @brief 主串口。
/// @return
bsp::ISerial &DI_Serial();

/// @brief 包含所有可用串口的集合。
/// @return
base::IReadOnlyCollection<std::string, bsp::ISerial *> &DI_SerialCollection();
#pragma endregion

#pragma region DMA
/// @brief 构造一个 bsp::IDmaOptions 对象并返回。它可以用来配置 DMA。
/// @return bsp::IDmaOptions 对象
std::shared_ptr<bsp::IDmaOptions> DICreate_DmaOptions();

/// @brief DMA 通道集合。
/// @return
base::IReadOnlyCollection<std::string, bsp::IDmaChannel *> &DI_DmaChannel();
#pragma endregion
