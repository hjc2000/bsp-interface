#pragma once
#include <base/stream/Span.h>
#include <bsp-interface/sdram/ISDRAMTiming.h>

namespace bsp
{
	/// @brief SDRAM 接口。
	class ISDRAMController
	{
	public:
		/// @brief 打开 SDRAM 控制器。
		/// @param timing
		virtual void Open(bsp::ISDRAMTiming const &timing) = 0;

		/// @brief 此 SDRAM 的内存段。
		/// @return
		virtual base::Span Span() const = 0;
	};
} // namespace bsp
