#pragma once
#include<base/stream/Stream.h>

namespace bsp
{
	class ISerial :public base::Stream
	{
	public:
		/// <summary>
		///		以指定的波特率启动串口。
		/// </summary>
		/// <param name="baud_rate"></param>
		virtual void Begin(uint32_t baud_rate) = 0;
	};
}
