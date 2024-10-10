#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/flash/IFlash.h>
#include <string>

/// @brief flash 集合。
/// @return
base::IDictionary<std::string, bsp::IFlash *> const &DI_FlashCollection();
