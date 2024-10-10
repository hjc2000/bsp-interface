#pragma once
#include <cstdint>
#include <functional>

namespace bsp
{
    /// @brief 任务管理器接口
    class ITaskManager
    {
    public:
        /// @brief 启动运行一个任务
        ///
        /// @param func 任务函数
        ///
        /// @param stack_size 任务栈大小。单位：字。
        /// @note 对于 32 位宽的 CPU ，一个字是 32 位，即 4 个字节。
        virtual void RunTask(std::function<void()> func, uint32_t stack_size) = 0;
    };
} // namespace bsp
