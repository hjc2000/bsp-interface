#pragma once
#include <bsp-interface/IHeap.h>

/// @brief 获取主堆。
/// @note 主堆是系统一启动，main 函数的第一条语句就能用的堆。这种堆通常是建立在 SRAM
/// 中，除非能在 main 函数执行之前就配置好 SDRAM 等外部内存。
/// @return
bsp::IHeap &DI_Heap();
