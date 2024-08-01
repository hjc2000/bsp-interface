#pragma once
#include <base/stream/Stream.h>
#include <bsp-interface/serial/ISerialOptions.h>
#include <string>

namespace bsp
{
	/// @brief 串口接口。
	class ISerial
		: public base::Stream
	{
	public:
		virtual std::string Name() = 0;

		/// @brief 以指定的波特率启动串口。
		virtual void Open(bsp::ISerialOptions const &options) = 0;

#pragma region Stream
		bool CanRead() override;
		bool CanWrite() override;
		bool CanSeek() override;

		int64_t Length() override;
		void SetLength(int64_t value) override;

		void Flush() override;

		int64_t Position() override;
		void SetPosition(int64_t value) override;
#pragma endregion
	};
}
