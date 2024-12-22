#pragma once
#include <stdint.h>

/// @brief 剩余堆大小。
/// @return
uint32_t DI_FreeHeapSize();

/// @brief 已经使用的堆大小。
/// @return
uint32_t DI_UsedHeapSize();
