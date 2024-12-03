#pragma once
#include <base/unit/Hz.h>

namespace bsp
{
    /// @brief 时钟信号
    class IClockSignal
    {
    public:
        /// @brief 时钟信号的名称。
        /// @return
        virtual std::string Name() const = 0;

        /// @brief 时钟信号的频率
        /// @return
        virtual base::Hz Frequency() const = 0;

        /// @brief 打开时钟信号。
        /// @param input_division_factor
        /// @param output_division_factor
        virtual void Open(uint32_t input_division_factor, uint32_t output_division_factor) = 0;
    };
} // namespace bsp
