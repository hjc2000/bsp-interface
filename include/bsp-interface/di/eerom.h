#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/eerom/IEEROM.h>
#include <string>

/// @brief EEROM 储存器集合。
/// @return
base::IDictionary<std::string, bsp::IEEROM *> const &DI_EEROMCollection();
