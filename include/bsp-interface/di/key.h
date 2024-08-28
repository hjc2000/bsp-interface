#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/key/IKeyScanner.h>

/// @brief 按键集合。
/// @return
base::IReadOnlyDictionary<std::string, bsp::IKey *> &DI_KeyCollection();

bsp::IKeyScanner &DI_KeyScanner();
