#pragma once
#include <base/stream/Span.h>
#include <bsp-interface/sdram/ISDRAMTimingProvider.h>

namespace bsp
{
	namespace sdram
	{
		namespace property
		{
			/// @brief 行地址的位数。
			class RowBitCount
			{
			public:
				explicit RowBitCount(int value)
					: _value(value)
				{
				}

				int _value = 0;
			};

			/// @brief 列地址的位数。
			class ColumnBitCount
			{
			public:
				explicit ColumnBitCount(int value)
					: _value(value)
				{
				}

				int _value = 0;
			};

			/// @brief 数据宽度，或者说数据总线位数。
			class DataWidth
			{
			public:
				explicit DataWidth(int value)
					: _value(value)
				{
				}

				int _value = 0;
			};

			/// @brief 读突发长度
			class ReadBurstLength
			{
			public:
				explicit ReadBurstLength(int value)
					: _value(value)
				{
				}

				int _value = 0;
			};
		} // namespace property

		/// @brief SDRAM 控制器接口。
		/// @note 这个接口用来封装类似于 stm32 的 FMC 接口的 SDRAM 控制器。
		class ISDRAMController
		{
		public:
			/// @brief 将 SDRAM 控制器以读突发的模式打开。写不突发。
			/// @param timing_provider
			/// @param row_bit_count
			/// @param column_bit_count
			/// @param data_width
			/// @param read_burst_length
			virtual void OpenAsReadBurstMode(bsp::sdram::ISDRAMTimingProvider const &timing_provider,
											 bsp::sdram::property::RowBitCount const &row_bit_count,
											 bsp::sdram::property::ColumnBitCount const &column_bit_count,
											 bsp::sdram::property::DataWidth const &data_width,
											 bsp::sdram::property::ReadBurstLength const &read_burst_length) = 0;

			/// @brief 发送：“预充电所有 BANK” 的命令。
			virtual void PrechargeAll() = 0;

			/// @brief 发送自动刷新命令。
			virtual void AutoRefresh() = 0;

			/// @brief 写模式寄存器。
			/// @param value
			virtual void WriteModeRegister(uint32_t value) = 0;
		};
	} // namespace sdram
} // namespace bsp
