#pragma once
#include <base/unit/MHz.h>

namespace bsp
{
#pragma region 参数类

	class IClockSignal_InputDivisionFactor
	{
	private:
		uint32_t _value = 0;

	public:
		explicit IClockSignal_InputDivisionFactor(uint32_t value)
		{
			_value = value;
		}

		uint32_t Value() const
		{
			return _value;
		}
	};

	class IClockSignal_OutputDivisionFactor
	{
	private:
		uint32_t _value = 0;

	public:
		explicit IClockSignal_OutputDivisionFactor(uint32_t value)
		{
			_value = value;
		}

		uint32_t Value() const
		{
			return _value;
		}
	};

	class IClockSignal_ClockSource
	{
	private:
		std::string _value;

	public:
		explicit IClockSignal_ClockSource(std::string const &value)
		{
			_value = value;
		}

		std::string Value() const
		{
			return _value;
		}
	};

#pragma endregion

	/// @brief 时钟信号
	class IClockSignal
	{
	public:
		/// @brief 时钟信号的名称。
		/// @return
		virtual std::string Name() const = 0;

		/// @brief 时钟信号的频率
		/// @return
		virtual base::MHz Frequency() const = 0;

		/// @brief 打开时钟信号。
		/// @note 有的时钟信号只有输入分频，没有输出分频，就使用本重载。
		/// @param input_division_factor
		virtual void Open(bsp::IClockSignal_InputDivisionFactor const &input_division_factor);

		/// @brief 打开时钟信号。
		/// @note 有的时钟信号只有输出分频，没有输入分频，就使用本重载。
		/// @param output_division_factor
		virtual void Open(bsp::IClockSignal_OutputDivisionFactor const &output_division_factor);

		/// @brief 打开时钟信号。
		/// @param output_division_factor 输出分频系数。
		/// @param clock_source 时钟源。像 stm32 的系统时钟 sysclk，是时钟源后的第一个时钟信号，输入端连接着
		/// 各个时钟源，输出端供给各个子时钟信号。本参数用来选择类似 sysclk 这种时钟信号的时钟源。
		virtual void Open(bsp::IClockSignal_OutputDivisionFactor const &output_division_factor,
						  IClockSignal_ClockSource const &clock_source);

		/// @brief 打开时钟信号。
		/// @note 有的时钟信号既有输入分频，又有输出分频，就使用本重载。
		/// @param input_division_factor
		/// @param output_division_factor
		virtual void Open(bsp::IClockSignal_InputDivisionFactor const &input_division_factor,
						  bsp::IClockSignal_OutputDivisionFactor const &output_division_factor);
	};
} // namespace bsp
