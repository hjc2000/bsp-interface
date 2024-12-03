#pragma once

/// @brief 复位单片机。
void DI_Reset();

/// @brief 执行基础的初始化工作。
/// @note 此函数需要实现为幂等。
void DI_DoBasicInitialization();
