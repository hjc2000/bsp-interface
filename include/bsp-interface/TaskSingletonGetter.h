#pragma once
#include "base/define.h"
#include "base/LockGuard.h"
#include "base/task/IMutex.h"
#include "bsp-interface/di/task.h"

namespace bsp
{
	///
	/// @brief 在任务函数中适用的单例获取器，避免多个任务同时获取一个单例造成
	/// 多次调用其构造函数。
	///
	/// @tparam T
	///
	template <typename T>
	class TaskSingletonGetter :
		protected base::ILock
	{
	private:
		inline static_field std::shared_ptr<base::IMutex> _lock = nullptr;
		inline static_field std::unique_ptr<T> _p;

		virtual void Lock() override
		{
			{
				bsp::di::task::TaskGuard g;
				if (_lock == nullptr)
				{
					_lock = base::CreateIMutex();
				}
			}

			_lock->Lock();
		}

		virtual void Unlock() override
		{
			_lock->Unlock();
		}

	protected:
		virtual std::unique_ptr<T> Create() = 0;

	public:
		///
		/// @brief 获取单例的引用
		///
		/// @return T&
		///
		T &Instance()
		{
			if (_p != nullptr)
			{
				return *_p;
			}

			base::LockGuard l{*this};
			if (_p != nullptr)
			{
				return *_p;
			}

			_p = Create();
			if (_p == nullptr)
			{
				throw std::runtime_error{"禁止将 Create 函数实现为返回空指针。"};
			}

			return *_p;
		}

		///
		/// @brief 重载解引用运算符，用来获取单例的引用。
		///
		/// @return T&
		///
		T &operator*()
		{
			return Instance();
		}

		///
		/// @brief 重载指针式的成员访问运算符，用来访问单例对象的成员。
		///
		/// @return T*
		///
		T *operator->()
		{
			return &Instance();
		}
	};
} // namespace bsp
