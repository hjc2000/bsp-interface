#pragma once
#include <bsp-interface/interrupt/IExtiManager.h>
#include <bsp-interface/interrupt/IsrManager.h>
#include <functional>
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

/// @brief 禁止全局中断
void DI_DisableGlobalInterrupt() noexcept;

/// @brief 启用全局中断
void DI_EnableGlobalInterrupt() noexcept;

/// @brief 外部中断管理器。
/// @return
bsp::IExtiManager &DI_ExtiManager();

#pragma region 已经实现
/// @brief 执行临界区工作。会通过禁用全局中断来保证安全。
/// @note 此函数已经实现。
/// @param func
void DI_DoGlobalCriticalWork(std::function<void()> func);

/// @brief 中断管理器。
/// @note 此依赖本库已经提供了，不需要实现此函数了。
/// @return
bsp::IsrManager &DI_IsrManager();
#pragma endregion
