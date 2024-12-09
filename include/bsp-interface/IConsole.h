#pragma once
#include <base/stream/ReadOnlySpan.h>
#include <base/stream/Stream.h>
#include <base/string/ICanToString.h>
#include <memory>
#include <string>

namespace bsp
{
    /// @brief 控制台接口
    class IConsole
    {
    public:
        /// @brief 控制台当前的输出流。
        /// @return
        virtual std::shared_ptr<base::Stream> OutStream() = 0;

        /// @brief 为本控制台设置用来输出的输出流。
        /// @note 如果没有设置过，则输出流为空，无法进行输出。
        /// @param value
        virtual void SetOutStream(std::shared_ptr<base::Stream> value) = 0;

        /// @brief 写一个字符。
        /// @param c
        void Write(char c);

        /// @brief 打印字符串。
        /// @param str
        void Write(char const *str);

        /// @brief 打印指定长度的字符缓冲区。
        /// @param str
        /// @param length
        void Write(char const *str, int length);

        /// @brief 打印字符串。
        /// @param str
        void Write(std::string const &str);

        /// @brief 将 ReadOnlySpan 逐个字节打印出来。每 20 个数一行。
        /// @param o
        void Write(base::ReadOnlySpan const &o);

        void Write(void *p);

        /// @brief 打印一条空行。
        void WriteLine();

        /// @brief 打印一行。
        /// @param str
        void WriteLine(char const *str);

        /// @brief 打印一行。
        /// @param str
        void WriteLine(std::string const &str);

        /// @brief 打印一行。
        /// @param o
        void WriteLine(base::ICanToString const &o);

        void WriteLine(void *p);

        /// @brief 打印一条空行。
        void WriteError() noexcept;

        /// @brief 错误汇报。
        /// @param str
        virtual void WriteError(char const *str) noexcept;

        /// @brief 错误汇报。
        /// @param str
        virtual void WriteError(std::string const &str) noexcept;

        /// @brief 错误汇报。
        /// @param o
        virtual void WriteError(base::ICanToString const &o) noexcept;
    };
} // namespace bsp
