#pragma once
#include <chrono>

namespace bsp
{
    /// @brief 独立看门狗接口。
    class IIndependentWatchDog
    {
    public:
        /// @brief 打开看门狗定时器。
        /// @param timeout 看门狗超时时间。
        virtual void Open(std::chrono::milliseconds timeout) = 0;

        /// @brief 关闭看门狗定时器。
        virtual void Close() = 0;

        /// @brief 看门狗超时时间。
        /// @return
        virtual std::chrono::milliseconds Timeout() const = 0;

        /// @brief 喂狗。
        virtual void Feed() = 0;
    };
} // namespace bsp
