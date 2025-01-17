#pragma once
#include <bsp-interface/task/IBinarySemaphore.h>
#include <bsp-interface/task/ITask.h>
#include <cstdint>
#include <functional>
#include <memory>

namespace bsp
{
	namespace di
	{
		namespace task
		{
			/// @brief 构造一个二进制信号量。
			/// @return
			std::shared_ptr<bsp::IBinarySemaphore> CreateBinarySemaphore();

			/// @brief 创建一个任务
			/// @param stack_size 任务栈大小。单位：字。
			/// @note 对于 32 位宽的 CPU ，一个字是 32 位，即 4 个字节。
			/// @param func 任务函数
			std::shared_ptr<bsp::ITask> CreateTask(uint32_t stack_size, std::function<void()> func);

			/// @brief 启动调度。本函数会持续阻塞。
			void StartScheduler();

			/// @brief 暂停所有调度。
			/// @warning 实现本函数时禁止使用动态内存分配，因为堆也需要本函数。
			void SuspendAllTask();

			/// @brief 恢复所有调度。
			/// @note 如果调度器没有启动，本函数不会启动调度器。
			/// @warning 实现本函数时禁止使用动态内存分配，因为堆也需要本函数。
			void ResumeAllTask();

			/// @brief 任务守卫。
			/// @note 构造时暂停所有任务的调度，析构时恢复所有任务的调度。
			class TaskGuard
			{
			public:
				TaskGuard()
				{
					SuspendAllTask();
				}

				~TaskGuard()
				{
					ResumeAllTask();
				}
			};
		} // namespace task
	} // namespace di
} // namespace bsp
