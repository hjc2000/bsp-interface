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

namespace bsp
{
	/// @brief 任务守卫。
	/// @note 构造时暂停所有任务的调度，析构时恢复所有任务的调度。
	class TaskGuard
	{
	public:
		TaskGuard()
		{
			DI_TaskManager().SuspendAllTask();
		}

		~TaskGuard()
		{
			DI_TaskManager().ResumeAllTask();
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
