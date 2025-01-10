#pragma once
#include <bsp-interface/IHeap.h>
#include <memory>

/// @brief 获取主堆。
/// @return
bsp::IHeap &DI_Heap();

std::shared_ptr<bsp::IHeap> DI_CreateHeap(uint8_t *buffer, size_t size);

#pragma region 已经实现
void DI_AddHeap(std::shared_ptr<bsp::IHeap> const &heap);
void DI_AddHeap(uint8_t *buffer, size_t size);
#pragma endregion
