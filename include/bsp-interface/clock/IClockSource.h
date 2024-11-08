#pragma once
#include <base/unit/Hz.h>
#include <cstdint>
#include <string>

namespace bsp
{
    /// @brief 时钟源状态
    enum class IClockSource_State
    {
        On,
        Off,
        Bypass,
    };

    /// @brief 时钟源接口
    class IClockSource
    {
    public:
        /// @brief 本时钟源的名称。
        /// @return
        virtual std::string Name() const = 0;

        /// @brief 打开时钟源。
        /// @param input_division 输入分频系数。
        /// @param output_division 输出分频系数。
        virtual void TurnOn(int32_t input_division,
                            int32_t output_division) = 0;

        /// @brief 打开时钟源。
        /// @note 输入分频和输出分频都设置为 1.
        void TurnOn();

        /// @brief 关闭时钟源。
        virtual void TurnOff() = 0;

        /// @brief 设置为旁路。
        /// @param external_clock_frequency 外部时钟频率。
        /// @param input_division 输入分频系数。
        /// @param output_division 输出分频系数。
        virtual void SetAsBypass(base::Hz external_clock_frequency,
                                 int32_t input_division,
                                 int32_t output_division) = 0;

        /// @brief 设置为旁路。
        /// @note 输入分频和输出分频都设置为 1.
        /// @param external_clock_frequency 外部时钟频率。
        void SetAsBypass(base::Hz external_clock_frequency);

        /// @brief 本时钟源当前的状态。
        /// @return
        virtual IClockSource_State State() const = 0;

        /// @brief 本时钟源当前频率。
        /// @return
        virtual base::Hz Frequency() const = 0;
    };
} // namespace bsp
