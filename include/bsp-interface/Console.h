#pragma once
#include <base/stream/Stream.h>
#include <memory>
#include <string>

namespace bsp
{
    /// @brief 单例控制台
    class Console final
    {
    private:
        Console() = default;
        Console(Console const &o) = delete;
        Console(Console const &&o) = delete;
        Console &operator=(Console const &o) = delete;
        Console &operator=(Console const &&o) = delete;

        std::shared_ptr<base::Stream> _out_stream;

    public:
        static Console &Instance()
        {
            static Console o;
            return o;
        }

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
