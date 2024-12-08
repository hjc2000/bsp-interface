#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/ExpandedIO/IExpandedIoPort.h>
#include <string>

/// @brief 扩展 IO 集合。
/// @return
base::IDictionary<std::string, bsp::IExpandedIoPort *> const &DI_ExpandedIoPortCollection();
