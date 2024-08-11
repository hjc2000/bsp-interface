#pragma once

namespace bsp
{
    /// @brief 数字 LED。只能开或关，无法调节亮度。
    class IDigitalLed
    {
    public:
        virtual ~IDigitalLed() = default;

        virtual void TurnOn() = 0;
        virtual void TurnOff() = 0;
        virtual void Toggle() = 0;

        /// @brief 指示该 LED 是否可以读取当前状态。
        /// @return
        virtual bool CanRead();

        /// @brief 需要 CanRead 返回 true，本方法才有效。
        /// @return
        virtual bool IsTurnedOn();

        /// @brief 需要 CanRead 返回 true，本方法才有效。
        /// @return
        virtual bool IsTurnedOff();
    };
} // namespace bsp
