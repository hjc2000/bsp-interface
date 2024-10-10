#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/serial/ISerial.h>
#include <memory>

std::shared_ptr<bsp::ISerialOptions> DICreate_ISerialOptions();

/// @brief 主串口。
/// @return
bsp::ISerial &DI_Serial();

/// @brief 包含所有可用串口的集合。
/// @return
base::IDictionary<std::string, bsp::ISerial *> const &DI_SerialCollection();
