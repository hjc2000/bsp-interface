#pragma once
#include <bsp-interface/task/IBinarySemaphore.h>
#include <bsp-interface/task/ITask.h>
#include <cstdint>
#include <functional>
#include <memory>

/// @brief 构造一个二进制信号量。
/// @return
std::shared_ptr<bsp::IBinarySemaphore> DICreate_BinarySemaphore();

/// @brief 创建一个任务
/// @param stack_size 任务栈大小。单位：字。
/// @note 对于 32 位宽的 CPU ，一个字是 32 位，即 4 个字节。
/// @param func 任务函数
std::shared_ptr<bsp::ITask> DI_CreateTask(uint32_t stack_size, std::function<void()> func);

/// @brief 启动调度。本函数会持续阻塞。
void DI_StartScheduler();

/// @brief 暂停所有调度。
void DI_SuspendAllTask();

/// @brief 恢复所有调度。
/// @note 如果调度器没有启动，本函数不会启动调度器。
void DI_ResumeAllTask();

namespace bsp
{
	/// @brief 任务守卫。
	/// @note 构造时暂停所有任务的调度，析构时恢复所有任务的调度。
	class TaskGuard
	{
	public:
		TaskGuard()
		{
			DI_SuspendAllTask();
		}

		~TaskGuard()
		{
			DI_ResumeAllTask();
		}
	};

	/// @brief 构造时暂停所有任务的调度，并且禁用全局中断。
	/// 析构时恢复所有任务的调度并且使能全局中断。
	class TaskAndGlobalInterruptGuard
	{
	public:
		TaskAndGlobalInterruptGuard();
		~TaskAndGlobalInterruptGuard();
	};
} // namespace bsp
