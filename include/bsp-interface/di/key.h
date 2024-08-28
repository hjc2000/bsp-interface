#pragma once
#include <base/container/ICollection.h>
#include <bsp-interface/key/IKeyScanner.h>

/// @brief 按键集合。
/// @return
base::ICollection<std::string, bsp::IKey *> const &DI_KeyCollection();

bsp::IKeyScanner &DI_KeyScanner();
