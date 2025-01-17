#pragma once
#include <base/di/SingletonGetter.h>
#include <base/task/IMutex.h>
#include <bsp-interface/di/task.h>

namespace bsp
{
	/// @brief 在任务函数中适用的单例获取器，避免多个任务同时获取一个单例造成
	/// 多次调用其构造函数。
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
				bsp::di::task::TaskGuard g;
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
