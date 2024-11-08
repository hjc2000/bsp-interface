#pragma once
#include <cstdint>

namespace bsp
{
    /// @brief 时钟源状态
    enum class IClockSource_State
    {
        On,
        Off,
        ByPass,
    };

    /// @brief 时钟源接口
    class IClockSource
    {
    public:
        /// @brief 配置时钟源
        /// @param state
        /// @param input_division
        /// @param output_division
        virtual void Configure(IClockSource_State state,
                               int32_t input_division,
                               int32_t output_division) = 0;
    };
} // namespace bsp
