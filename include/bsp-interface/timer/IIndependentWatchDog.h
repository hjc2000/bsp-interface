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
        /// @note 有的单片机的独立看门狗一旦开启后就关不掉了，调用本函数不会起作用。
        virtual void Close() = 0;

        /// @brief 看门狗超时时间。
        /// @return
        virtual std::chrono::milliseconds Timeout() const = 0;

        /// @brief 喂狗。
        virtual void Feed() = 0;
    };
} // namespace bsp
