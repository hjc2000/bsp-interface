#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/iic/IIicHost.h>
#include <string>

/// @brief IIC 主机接口的集合。
/// @return
base::IDictionary<std::string, bsp::IIicHost *> const &DI_IicHostCollection();
