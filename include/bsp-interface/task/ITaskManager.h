#pragma once
#include <bsp-interface/task/ITask.h>
#include <cstdint>
#include <functional>
#include <memory>

namespace bsp
{
    /// @brief 任务管理器接口
    class ITaskManager
    {
    public:
        /// @brief 创建一个任务
        ///
        /// @param func 任务函数
        ///
        /// @param stack_size 任务栈大小。单位：字。
        /// @note 对于 32 位宽的 CPU ，一个字是 32 位，即 4 个字节。
        virtual std::shared_ptr<bsp::ITask> Create(std::function<void()> func, uint32_t stack_size) = 0;

        /// @brief 启动调度。本函数会持续阻塞。
        virtual void StartScheduler() = 0;
    };
} // namespace bsp
