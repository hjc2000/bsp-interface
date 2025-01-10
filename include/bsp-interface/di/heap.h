#pragma once
#include <bsp-interface/IHeap.h>
#include <memory>

/// @brief 获取主堆。
/// @return
bsp::IHeap &DI_Heap();

void DI_AddHeap(std::shared_ptr<bsp::IHeap> const &heap);
