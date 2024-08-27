#pragma once
#include <base/container/ICollection.h>
#include <bsp-interface/flash/IFlash.h>
#include <string>

/// @brief flash 集合。
/// @return
base::IReadOnlyCollection<std::string, bsp::IFlash *> &DI_FlashCollection();
