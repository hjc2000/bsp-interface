#pragma once
#include <chrono>
#include <functional>

namespace bsp
{
    /// @brief 定时器接口。
    class IBaseTimer
    {
    public:
        /// @brief 初始化定时器
        /// @param period 定时周期
        virtual void Open() = 0;

        /// @brief 启动定时器。
        virtual void Start(std::chrono::milliseconds period) = 0;

        /// @brief 停止定时器。
        virtual void Stop() = 0;

        /// @brief 设置定时时间到触发的回调。
        /// @note 设置为 nullptr 可以取消回调。
        /// @param func
        virtual void SetPeriodElapsedCallback(std::function<void()> func) = 0;
    };
} // namespace bsp
