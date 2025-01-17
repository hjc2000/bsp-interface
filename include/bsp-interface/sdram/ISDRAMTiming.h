#pragma once
#include <base/unit/Nanoseconds.h>

namespace bsp
{
	/// @brief SDRAM 时序。
	class ISDRAMTiming
	{
	public:
		/// @brief 时钟信号周期。
		/// @return
		virtual base::Nanoseconds T_CLK() = 0;

		/// @brief 行循环时间。
		/// @note 本次激活一行到下一次激活一行的时间间隔。
		/// @return
		virtual base::Nanoseconds T_RC() = 0;

		/// @brief 模式寄存器设置延迟。
		/// @note 设置模式寄存器后要等待这么长时间才可以进行下一个命令。
		/// 	@li 设置模式寄存器后要等待 T_RSC 后才可以进行下一次的设置模式寄存器。
		/// 	@li 设置模式寄存器后要等待 T_RSC 后才可以激活一行。
		/// 	@li 设置模式寄存器后要等待 T_RSC 后才可以发送自动刷新命令。
		/// @return
		virtual base::Nanoseconds T_RSC() = 0;

		/// @brief 自动刷新时间。
		/// @note 至少这么长时间刷新一次所有行。如果超过这么长时间没有刷新完所有行，数据有可能丢失。
		/// @note T_REF 指示了 SDRAM 内部电容能够将电压保持在安全范围的时间。
		/// @note 发送一次自动刷新命令会刷新一行。SDRAM 内部有一个计数器，每次发送自动刷新命令都会
		/// 刷新计数器的当前行然后递增计数器。如果有 8192 行，则必须在 T_REF 时间内发送超过 8192 次
		/// 自动刷新命令，这样才能保证数据安全。
		/// @return
		virtual base::Nanoseconds T_REF() = 0;

		/// @brief SDRAM 的行数。
		/// @return
		virtual int64_t RowCount() = 0;

		/// @brief 发送自动刷新命令的时间间隔。
		/// @return
		base::Nanoseconds T_AutoRefreshCommand()
		{
			return T_REF() / RowCount();
		}
	};
} // namespace bsp
