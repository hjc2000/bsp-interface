#pragma once
#include <base/di/SingletonGetter.h>
#include <bsp-interface/di/task.h>

namespace bsp
{
	/// @brief 通过暂停所有任务的调度来保证单例构造的安全。
	/// @tparam T
	template <typename T>
	class TaskSingletonGetter :
		public base::SingletonGetter<T>
	{
	public:
		virtual void Lock() override
		{
			DI_SuspendAllTask();
		}

		virtual void Unlock() override
		{
			DI_ResumeAllTask();
		}
	};
} // namespace bsp
