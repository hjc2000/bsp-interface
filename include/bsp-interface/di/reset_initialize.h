#pragma once

/// @brief 复位单片机。
void DI_Reset();

/// @brief 初始化 CPU.
/// @note 本函数需要被 DI_Initialize 调用。别的地方都不要调用。
/// @note 这里用来执行一些非常底层的 CPU 的初始化，甚至比时钟配置还要底层。
/// 例如使能 FPU，使能 cache，开启第二个核心，......等。
void DI_InitializeCPU();

/// @brief 执行初始化工作。
/// @note 此函数需要实现为幂等。
/// @note 这个函数需要在 main 函数一开始调用。
/// @note 这个函数需要在最终的 BSP 或者可执行文件项目中实现，因为这样才能将所有初始化工作
/// 包含到这个函数中。
/// @warning 本函数不可重入，不是线程安全。
void DI_Initialize();
