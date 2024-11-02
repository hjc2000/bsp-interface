#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/serial/ISerial.h>
#include <memory>

/// @brief 创建一个配置选项对象。
/// @note 默认的选项为：1 位起始位，8 位数据位，1 位停止位，无校验，波特率 115200，
/// 无硬件流控，数据双向传输。
/// @return
std::shared_ptr<bsp::ISerialOptions> DICreate_ISerialOptions();

/// @brief 主串口。
/// @return
bsp::ISerial &DI_Serial();

/// @brief 包含所有可用串口的集合。
/// @return
base::IDictionary<std::string, bsp::ISerial *> const &DI_SerialCollection();
