#pragma once
#include <base/define.h>
#include <base/stream/Stream.h>
#include <bsp-interface/interrupt/IInterruptSwitch.h>
#include <memory>
#include <string>

namespace bsp
{
    /// @brief 单例控制台
    class Console
    {
    private:
        Console() = default;

        std::shared_ptr<base::Stream> _out_stream;

    public:
        static_function Console &Instance();

        std::shared_ptr<base::Stream> OutStream();

        /// @brief 为本控制台设置用来输出的输出流。
        /// @note 如果没有设置过，则输出流为空，无法进行输出。
        /// @param value
        void SetOutStream(std::shared_ptr<base::Stream> value);

        void Write(std::string const &str);
        void WriteLine(std::string const &str);
        void Write(char const *str);
        void WriteLine(char const *str);

        /// @brief 错误汇报。
        /// @param str
        void WriteError(char const *str) noexcept;

        /// @brief 错误汇报。
        /// @param str
        void WriteError(std::string const &str) noexcept;
    };
} // namespace bsp
