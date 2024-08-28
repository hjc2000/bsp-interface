#pragma once
#include <base/container/ICollection.h>
#include <bsp-interface/flash/IFlash.h>
#include <string>

/// @brief flash 集合。
/// @return
base::ICollection<std::string, bsp::IFlash *> const &DI_FlashCollection();
