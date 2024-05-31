#pragma once
#include<base/stream/Stream.h>
#include<memory>
#include<string>

namespace bsp
{
	class Console
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

		std::shared_ptr<base::Stream> OutStream()
		{
			return _out_stream;
		}

		void SetOutStream(std::shared_ptr<base::Stream> value)
		{
			_out_stream = value;
		}

		void Write(std::string const &str);
		void WriteLine(std::string const &str);
		void Write(char const *str);
		void WriteLine(char const *str);

		/// <summary>
		///		错误汇报。
		///		* 尝试利用串口输出错误信息。
		///		* 本函数不会抛出异常，内部捕获了所有异常，这确保当串口不可用，
		///		  串口类抛出异常时不会导致异常逃逸。因为 WriteError 是设计
		///		  为在 catch 块中使用的，而 catch 块一般不再嵌套 try-catch。
		///		* 严重错误时可能会连本函数都用不了。
		/// </summary>
		/// <param name="str"></param>
		void WriteError(char const *str) noexcept;
		void WriteError(std::string const &str) noexcept;
	};
}