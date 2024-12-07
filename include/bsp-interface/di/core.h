#pragma once

/// @brief 复位单片机。
void DI_Reset();

/// @brief 执行初始化工作。
/// @note 此函数需要实现为幂等。
/// @warning 本函数不可重入，不是线程安全。
void DI_Initialize();
