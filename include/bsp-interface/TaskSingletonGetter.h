#pragma once
#include <base/di/SingletonGetter.h>
#include <base/task/IMutex.h>
#include <bsp-interface/di/task.h>

namespace bsp
{
	/// @brief 通过暂停所有任务的调度来保证单例构造的安全。
	/// @tparam T
	template <typename T>
	class TaskSingletonGetter :
		public base::SingletonGetter<T>
	{
	private:
		inline static_field std::shared_ptr<base::IMutex> _lock = nullptr;

	protected:
		virtual void Lock() override
		{
			{
				bsp::TaskGuard g;
				if (_lock == nullptr)
				{
					_lock = base::di::CreateMutex();
				}
			}

			_lock->Lock();
		}

		virtual void Unlock() override
		{
			_lock->Unlock();
		}
	};
} // namespace bsp
