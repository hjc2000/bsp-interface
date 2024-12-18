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
		virtual void Write(char c) = 0;

		/// @brief 打印字符串。
		/// @param str
		virtual void Write(char const *str) = 0;

		/// @brief 打印指定长度的字符缓冲区。
		/// @param str
		/// @param length
		virtual void Write(char const *str, int length) = 0;

		/// @brief 打印字符串。
		/// @param str
		virtual void Write(std::string const &str) = 0;

		/// @brief 将 ReadOnlySpan 逐个字节打印出来。每 20 个数一行。
		/// @param o
		virtual void Write(base::ReadOnlySpan const &o) = 0;

		/// @brief 打印指针。
		/// @param p
		virtual void Write(void *p) = 0;

		/// @brief 打印一条空行。
		virtual void WriteLine() = 0;

		/// @brief 打印一行。
		/// @param str
		virtual void WriteLine(char const *str) = 0;

		/// @brief 打印一行。
		/// @param str
		virtual void WriteLine(std::string const &str) = 0;

		/// @brief 打印一行。
		/// @param o
		virtual void WriteLine(base::ICanToString const &o) = 0;

		/// @brief 打印指针。
		/// @param p
		virtual void WriteLine(void *p) = 0;

		/// @brief 打印一条空行。
		virtual void WriteError() noexcept = 0;

		/// @brief 错误汇报。
		/// @param str
		virtual void WriteError(char const *str) noexcept = 0;

		/// @brief 错误汇报。
		/// @param str
		virtual void WriteError(std::string const &str) noexcept = 0;

		/// @brief 错误汇报。
		/// @param o
		virtual void WriteError(base::ICanToString const &o) noexcept = 0;
	};
} // namespace bsp
