#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/key/IKeyScanner.h>

/// @brief 按键集合。
/// @return
base::IDictionary<std::string, bsp::IKey *> const &DI_KeyCollection();

#pragma region 已经实现
/// @brief 获取按键扫描器。
/// @note 本函数已经实现。
/// @return
bsp::IKeyScanner &DI_KeyScanner();
#pragma endregion
