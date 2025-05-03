#pragma once

/// @brief 复位单片机。
void DI_Reset();

/// @brief 执行初始化工作。
/// @note 此函数需要实现为幂等。
/// @note 这个函数需要在 main 函数一开始调用。
/// @note 这个函数需要在最终的 BSP 或者可执行文件项目中实现，因为这样才能将所有初始化工作
/// 包含到这个函数中。
/// @warning 本函数不可重入，不是线程安全。
void DI_Initialize();
