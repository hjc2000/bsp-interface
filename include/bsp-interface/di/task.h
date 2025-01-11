#pragma once
#include <base/di/SingletonGetter.h>
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

	template <typename T>
	class TaskSingletonGetter :
		public base::SingletonGetter<T>
	{
	public:
		void Lock() override
		{
			DI_TaskManager().SuspendAllTask();
		}

		void Unlock() override
		{
			DI_TaskManager().ResumeAllTask();
		}
	};
} // namespace bsp
