#pragma once
#include <base/task/IMutex.h>
#include <bsp-interface/di/task.h>
#include <Console.h>

namespace bsp
{
	class SafeConsole :
		public bsp::IConsole
	{
	private:
		std::shared_ptr<base::IMutex> _lock = base::CreateIMutex();
		bsp::IConsole *_console = &Console::Instance();

	public:
		static_function SafeConsole &Instance();

		/// @brief 控制台当前的输出流。
		/// @return
		std::shared_ptr<base::Stream> OutStream() override;

		/// @brief 为本控制台设置用来输出的输出流。
		/// @note 如果没有设置过，则输出流为空，无法进行输出。
		/// @param value
		void SetOutStream(std::shared_ptr<base::Stream> value) override;

		/// @brief 写一个字符。
		/// @param c
		void Write(char c) override;

		/// @brief 打印字符串。
		/// @param str
		void Write(char const *str) override;

		/// @brief 打印指定长度的字符缓冲区。
		/// @param str
		/// @param length
		void Write(char const *str, int length) override;

		/// @brief 打印字符串。
		/// @param str
		void Write(std::string const &str) override;

		/// @brief 将 ReadOnlySpan 逐个字节打印出来。每 20 个数一行。
		/// @param o
		void Write(base::ReadOnlySpan const &o) override;

		/// @brief 打印指针。
		/// @param p
		void Write(void const *p) override;

		/// @brief 打印一条空行。
		void WriteLine() override;

		/// @brief 打印一行。
		/// @param str
		void WriteLine(char const *str) override;

		/// @brief 打印一行。
		/// @param str
		void WriteLine(std::string const &str) override;

		/// @brief 打印一行。
		/// @param o
		void WriteLine(base::ICanToString const &o) override;

		/// @brief 打印指针。
		/// @param p
		void WriteLine(void const *p) override;

		/// @brief 打印一条空行。
		void WriteError() noexcept override;

		/// @brief 错误汇报。
		/// @param str
		void WriteError(char const *str) noexcept override;

		/// @brief 错误汇报。
		/// @param str
		void WriteError(std::string const &str) noexcept override;

		/// @brief 错误汇报。
		/// @param o
		void WriteError(base::ICanToString const &o) noexcept override;
	};
} // namespace bsp
