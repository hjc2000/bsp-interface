#pragma once
#include <bsp-interface/task/IBinarySemaphore.h>
#include <bsp-interface/task/IMutex.h>
#include <bsp-interface/task/ITaskManager.h>
#include <memory>

/// @brief 构造一个互斥量。
/// @return
std::shared_ptr<bsp::IMutex> DICreate_Mutex();

/// @brief 构造一个二进制信号量。
/// @return
std::shared_ptr<bsp::IBinarySemaphore> DICreate_BinarySemaphore();

/// @brief 获取任务管理器。
/// @return
bsp::ITaskManager &DI_TaskManager();
