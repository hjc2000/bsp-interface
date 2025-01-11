#pragma once
#include <bsp-interface/task/IBinarySemaphore.h>
#include <bsp-interface/task/ITaskManager.h>
#include <memory>

/// @brief 构造一个二进制信号量。
/// @return
std::shared_ptr<bsp::IBinarySemaphore> DICreate_BinarySemaphore();

/// @brief 获取任务管理器。
/// @return
bsp::ITaskManager &DI_TaskManager();

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
