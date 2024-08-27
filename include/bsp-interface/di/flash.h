#pragma once
#include <base/container/ICollection.h>
#include <bsp-interface/flash/IFlash.h>
#include <string>

base::IReadOnlyCollection<std::string, bsp::IFlash *> &DI_FlashCollection();
