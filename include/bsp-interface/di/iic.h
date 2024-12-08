#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/iic/IIicHost.h>
#include <string>

/// @brief IIC 主机接口的集合。
/// @warning 在实现本函数提供 IIicHost 对象时，如果 IIicHost 对象本身不是线程安全的，
/// 注意要使用 MutexIicHost 类包装一下再放入字典中。
/// @return
base::IDictionary<std::string, bsp::IIicHost *> const &DI_IicHostCollection();
