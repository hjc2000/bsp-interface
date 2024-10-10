#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/key/IKeyScanner.h>

/// @brief 按键集合。
/// @return
base::IDictionary<std::string, bsp::IKey *> const &DI_KeyCollection();

bsp::IKeyScanner &DI_KeyScanner();
