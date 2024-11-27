#pragma once
#include <base/container/IDictionary.h>
#include <base/unit/Hz.h>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace bsp
{
#pragma region 参数类
    /// @brief 时钟源状态
    enum class IClockSource_State
    {
        On,
        Off,
        Bypass,
    };

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

    /// @brief 时钟源接口。
    /// @note 时钟源各种各样，每种时钟源适合不同的 Open 函数。实现者应该给用户一个文档，文档中列出了所有时钟源的名称，
    /// 以及它们适用的 Open 函数。
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
        /// @param input_channel_name 输入通道名称。有的时钟源可能具有多个输入通道，例如可以从多个晶振中选择一个，
        /// 或者 PLL 可以从多个时钟源中选择一个。
        virtual void Open(std::string const &input_channel_name);

        /// @brief 用户自己决定输入通道和各个分频、倍频系数。
        /// @param input_channel_name 输入通道名。
        /// @param factors 分频、倍频系数都放在这个字典里，使用不同的名称来区分是什么。
        virtual void Open(std::string const &input_channel_name, base::IDictionary<std::string, int> const &factors);
#pragma endregion

#pragma region SetAsBypass
        /// @brief 设置为旁路。
        /// @param external_clock_frequency 外部时钟频率。
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

        /// @brief 本时钟源当前频率。这个重载版本适用于只有单个输出通道的时钟源。
        /// @return
        virtual base::Hz Frequency() const;

        /// @brief 查看某一个输出通道的频率。有的时钟源会有多个输出通道。
        /// @param output_channel_name 输出通道名。
        /// @return
        virtual base::Hz Frequency(std::string const &output_channel_name) const;
    };
} // namespace bsp
