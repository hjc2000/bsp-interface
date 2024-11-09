#pragma once
#include <base/container/IDictionary.h>
#include <base/unit/Hz.h>
#include <cstdint>
#include <stdexcept>
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

#pragma region 参数类

    class IClockSource_TargetOutputFrequency
    {
    private:
        base::Hz _value{};

    public:
        explicit IClockSource_TargetOutputFrequency(base::Hz const &value)
        {
            _value = value;
        }

        base::Hz Value() const
        {
            return _value;
        }

        void SetValue(base::Hz const &value)
        {
            _value = value;
        }
    };

#pragma endregion

    /// @brief 时钟源接口
    class IClockSource
    {
    public:
        /// @brief 本时钟源的名称。
        /// @return
        virtual std::string Name() const = 0;

#pragma region Open
        /// @brief 打开时钟源。
        /// @note 有的时钟源使用内部振荡器，不需要外部晶振，振荡器频率已知且固定，无法自定义，
        /// 直接打开就行。本重载用于这种场景。
        virtual void Open();

        /// @brief 打开时钟源。
        /// @note 有的时钟源非常简单，外部振荡器输入后，直接就输出同频率的时钟信号，
        /// 不支持分频和倍频。本重载用于这种简单的时钟源。
        /// @param crystal_frequency
        virtual void Open(base::Hz const &crystal_frequency);

        /// @brief 打开时钟源。
        /// @param input_channel_name
        virtual void Open(std::string const &input_channel_name);

        /// @brief 打开时钟源。
        /// @param target_output_frequency 目标输出频率
        virtual void Open(IClockSource_TargetOutputFrequency const &target_output_frequency);

        /// @brief 打开时钟源。
        /// @param target_output_frequencies 想让本时钟源输出的目标频率列表。因为有的时钟源可能有多个输出
        /// 通道，所以就采用了列表的形式。
        virtual void Open(base::IDictionary<std::string, base::Hz> const &target_output_frequencies);

        /// @brief 打开时钟源。
        /// @param input_channel_name 输入通道名。因为有的时钟源可能有多个输入通道，所以使用字符串指定
        /// 输入通道名。
        /// @param target_output_frequencies 想让本时钟源输出的目标频率列表。因为有的时钟源可能有多个输出
        /// 通道，所以就采用了列表的形式。
        virtual void Open(std::string const &input_channel_name,
                          base::IDictionary<std::string, base::Hz> const &target_output_frequencies);

        /// @brief 打开时钟源。
        /// @param input_channel_name 输入通道名。因为有的时钟源可能有多个输入通道，所以使用字符串指定
        /// 输入通道名。
        /// @param crystal_frequency 外部晶振频率。有的时钟源需要外部晶振，且晶振允许的频率是一个范围，
        /// 此时需要告诉本对象该晶振的频率才能打开本时钟源。这种情况下必须使用本 TurnOn 重载，
        /// 否则会抛出异常。
        /// @param target_output_frequencies 想让本时钟源输出的目标频率的字典。因为有的时钟源可能有多个
        /// 输出通道，所以就采用字典来指定每个通道，key 为输出通道名，value 为输出通道目标频率。
        virtual void Open(std::string const &input_channel_name,
                          base::Hz const &crystal_frequency,
                          base::IDictionary<std::string, base::Hz> const &target_output_frequencies);
#pragma endregion

#pragma region SetAsBypass
        /// @brief 设置为旁路。
        /// @param external_clock_frequency
        virtual void SetAsBypass(base::Hz external_clock_frequency);

        /// @brief 设置为旁路。
        /// @param external_clock_frequency 外部时钟频率。
        /// @param target_output_frequencies 想让本时钟源输出的目标频率列表。因为有的时钟源可能有多个输出
        /// 通道，所以就采用了列表的形式。
        virtual void SetAsBypass(base::Hz external_clock_frequency,
                                 base::IDictionary<std::string, base::Hz> const &target_output_frequencies);
#pragma endregion

        /// @brief 关闭时钟源。
        virtual void Close() = 0;

        /// @brief 本时钟源当前的状态。
        /// @return
        virtual IClockSource_State State() const = 0;

        /// @brief 本时钟源当前频率。
        /// @return
        virtual base::Hz Frequency() const = 0;
    };
} // namespace bsp
