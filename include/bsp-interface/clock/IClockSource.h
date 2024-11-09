#pragma once
#include <base/unit/Hz.h>
#include <cstdint>
#include <string>
#include <vector>

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
        /// @param crystal_frequency 有的时钟源需要外部晶振，且晶振允许的频率是一个范围，
        /// 此时需要告诉本对象该晶振的频率才能打开本时钟源。这种情况下必须使用本 TurnOn 重载，
        /// 否则会抛出异常。
        /// @param target_frequencies 想让本时钟源输出的目标频率列表。因为有的时钟源可能有多个输出
        /// 通道，所以就采用了列表的形式。
        virtual void TurnOn(base::Hz const &crystal_frequency,
                            std::vector<base::Hz> const &target_frequencies) = 0;

        /// @brief 打开时钟源。
        /// @param target_frequencies 想让本时钟源输出的目标频率列表。因为有的时钟源可能有多个输出
        /// 通道，所以就采用了列表的形式。
        virtual void TurnOn(std::vector<base::Hz> const &target_frequencies) = 0;

        /// @brief 关闭时钟源。
        virtual void TurnOff() = 0;

        /// @brief 设置为旁路。
        /// @param external_clock_frequency 外部时钟频率。
        /// @param target_frequencies 想让本时钟源输出的目标频率列表。因为有的时钟源可能有多个输出
        /// 通道，所以就采用了列表的形式。
        virtual void SetAsBypass(base::Hz external_clock_frequency,
                                 std::vector<base::Hz> const &target_frequencies) = 0;

        /// @brief 本时钟源当前的状态。
        /// @return
        virtual IClockSource_State State() const = 0;

        /// @brief 本时钟源当前频率。
        /// @return
        virtual base::Hz Frequency() const = 0;
    };
} // namespace bsp
