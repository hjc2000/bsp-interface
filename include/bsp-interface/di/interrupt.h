#pragma once
#include <bsp-interface/interrupt/IExtiManager.h>
#include <bsp-interface/interrupt/IIsrManager.h>
#include <stdint.h>

/// @brief 禁用 irq 指定的中断。
/// @param irq
void DI_DisableInterrupt(uint32_t irq) noexcept;

/// @brief 启用 irq 指定的中断。
/// @param irq
void DI_EnableInterrupt(uint32_t irq) noexcept;

/// @brief 使能指定 irq 的中断。
/// @param irq 中断号。
/// @param priority 优先级。
void DI_EnableInterrupt(uint32_t irq, uint32_t priority) noexcept;

/// @brief 外部中断管理器。
/// @return
bsp::IExtiManager &DI_ExtiManager();

#pragma region 已经实现
/// @brief 中断管理器。
/// @note 此依赖本库已经提供了，不需要实现此函数了。
/// @return
bsp::IIsrManager &DI_IsrManager();
#pragma endregion
