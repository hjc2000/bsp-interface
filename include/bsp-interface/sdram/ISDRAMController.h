#pragma once
#include <base/stream/Span.h>
#include <bsp-interface/sdram/ISDRAMTiming.h>

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
			/// @param timing
			/// @param row_bit_count
			/// @param column_bit_count
			/// @param data_width
			/// @param read_burst_length
			virtual void OpenAsReadBurstMode(bsp::sdram::ISDRAMTiming const &timing,
											 bsp::sdram::property::RowBitCount const &row_bit_count,
											 bsp::sdram::property::ColumnBitCount const &column_bit_count,
											 bsp::sdram::property::DataWidth const &data_width,
											 bsp::sdram::property::ReadBurstLength const &read_burst_length) = 0;
		};
	} // namespace sdram
} // namespace bsp
