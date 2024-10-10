#pragma once

namespace bsp
{
    /// @brief 二进制信号量接口
    class IBinarySemaphore
    {
    public:
        virtual void Release() = 0;
        virtual void ReleaseFromISR() = 0;
        virtual void Acquire() = 0;
    };
} // namespace bsp
