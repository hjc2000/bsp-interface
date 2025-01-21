#pragma once
#include <bsp-interface/sdram/ISDRAMTiming.h>

namespace bsp
{
	namespace sdram
	{
		namespace chip
		{
			/// @brief W9825G6KH-6 SDRAM 芯片的时序。
			/// @note 最大时钟频率：133MHz.
			class W9825G6KH_6_Timing :
				public bsp::sdram::ISDRAMTiming
			{
			private:
				/// @brief 时钟周期。
				base::Nanoseconds _t_clk;

			public:
				W9825G6KH_6_Timing(base::Nanoseconds const &t_clk);

				/// @brief 时钟信号周期。
				/// @return
				virtual base::Nanoseconds T_CLK() const override;

				/// @brief 模式寄存器设置延迟。
				/// @note 设置模式寄存器后要等待这么长时间才可以进行下一个命令。
				/// 	@li 设置模式寄存器后要等待 T_RSC 后才可以进行下一次的设置模式寄存器。
				/// 	@li 设置模式寄存器后要等待 T_RSC 后才可以发送行激活命令。
				/// 	@li 设置模式寄存器后要等待 T_RSC 后才可以发送自动刷新命令。
				/// @return
				virtual base::Nanoseconds T_RSC() const override;

				/// @brief 退出自刷新模式的时间。
				/// @note 注意：“自刷新” 不是 “自动刷新”
				/// @return
				virtual base::Nanoseconds T_XSR() const override;

				/// @brief 从行激活到预充电的时间。
				/// @note 激活一行后，至少保持 T_RAS 后才能发送预充电命令关闭这行。例如在写的时候，如果 SDRAM
				/// 还没来得及储存好写入的数据，就直接发送预充电命令关闭这行，数据可能会写失败。
				/// @return
				virtual base::Nanoseconds T_RAS() const override;

				/// @brief 行循环时间。
				/// @note 本次激活一行到下一次激活一行的时间间隔。
				/// @return
				virtual base::Nanoseconds T_RC() const override;

				/// @brief 写恢复时间。
				/// @note 发送写命令后，至少将信号保持 T_WR 后才能撤掉信号进入下一个命令。下一个命令可以是写命令，
				/// 也可以是预充电命令。如果使用了自动预充电的写模式，则 SDRAM 内部会自己在 T_WR 后进行预充电。
				/// @return
				virtual base::Nanoseconds T_WR() const override;

				/// @brief 预充电命令后的延迟。
				/// @note 发送预充电命令后要等待 T_RP 才可以进行下一个命令。如果使用了自动预充电读写模式，也是要在 SDRAM
				/// 内部自动预充电后再继续等待 T_RP.
				/// @return
				virtual base::Nanoseconds T_RP() const override;

				/// @brief 行到列时间。
				/// @note 读写数据需要先发送行激活命令激活其中一行，然后发送读写命令选中其中一列（列地址信号是读写命令的一部分）。
				/// 发送行激活命令后要 T_RCD 后才能发送读写命令。
				/// @return
				virtual base::Nanoseconds T_RCD() const override;

				/// @brief 自动刷新时间。
				/// @note 至少这么长时间刷新一次所有行。如果超过这么长时间没有刷新完所有行，数据有可能丢失。
				/// @note T_REF 指示了 SDRAM 内部电容能够将电压保持在安全范围的时间。
				/// @note 发送一次自动刷新命令会刷新一行。SDRAM 内部有一个计数器，每次发送自动刷新命令都会
				/// 刷新计数器的当前行然后递增计数器。如果有 8192 行，则必须在 T_REF 时间内发送超过 8192 次
				/// 自动刷新命令，这样才能保证数据安全。
				/// @return
				virtual base::Nanoseconds T_REF() const override;

				/// @brief SDRAM 的行数。
				/// @return
				virtual int64_t RowCount() const override;
			};
		} // namespace chip
	} // namespace sdram
} // namespace bsp
