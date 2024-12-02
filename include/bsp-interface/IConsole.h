#pragma once
#include <base/stream/Stream.h>
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

        /// @brief 打印字符串。
        /// @param str
        void Write(char const *str);

        /// @brief 打印字符串。
        /// @param str
        void Write(std::string const &str);

        /// @brief 打印一条空行。
        void WriteLine();

        /// @brief 打印一行。
        /// @param str
        void WriteLine(char const *str);

        /// @brief 打印一行。
        /// @param str
        void WriteLine(std::string const &str);

        /// @brief 打印一条空行。
        void WriteError();

        /// @brief 错误汇报。
        /// @param str
        virtual void WriteError(char const *str) noexcept;

        /// @brief 错误汇报。
        /// @param str
        virtual void WriteError(std::string const &str) noexcept;
    };
} // namespace bsp
