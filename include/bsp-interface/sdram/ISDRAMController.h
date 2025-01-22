#pragma once
#include <base/stream/Span.h>
#include <bsp-interface/sdram/ISDRAMTiming.h>

namespace bsp
{
	namespace sdram
	{
		namespace property
		{
			class RowCount
			{
			public:
				explicit RowCount(int value)
					: _value(value)
				{
				}

				int _value = 0;
			};

			class ColumnCount
			{
			public:
				explicit ColumnCount(int value)
					: _value(value)
				{
				}

				int _value = 0;
			};

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
			/// @param row_count
			/// @param column_count
			/// @param data_width
			/// @param read_burst_length
			virtual void OpenAsReadBurstMode(bsp::sdram::ISDRAMTiming const &timing,
											 bsp::sdram::property::RowCount const &row_count,
											 bsp::sdram::property::ColumnCount const &column_count,
											 bsp::sdram::property::DataWidth const &data_width,
											 bsp::sdram::property::ReadBurstLength const &read_burst_length) = 0;
		};
	} // namespace sdram
} // namespace bsp
