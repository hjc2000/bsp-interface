#pragma once
#include <base/define.h>
#include <bsp-interface/IConsole.h>

namespace bsp
{
	/// @brief 单例控制台
	class Console :
		public bsp::IConsole
	{
	private:
		Console() = default;

		std::shared_ptr<base::Stream> _out_stream;

	public:
		static_function Console &Instance();

		/// @brief 控制台当前的输出流。
		/// @return
		std::shared_ptr<base::Stream> OutStream() override;

		/// @brief 为本控制台设置用来输出的输出流。
		/// @note 如果没有设置过，则输出流为空，无法进行输出。
		/// @param value
		void SetOutStream(std::shared_ptr<base::Stream> value) override;
	};
} // namespace bsp
