#pragma once
#include "base/container/IDictionary.h"
#include "bsp-interface/serial/ISerial.h"

namespace bsp
{
	namespace di
	{
		namespace serial
		{
			///
			/// @brief 主串口。
			/// @return
			///
			bsp::serial::ISerial &Serial();

			///
			/// @brief 包含所有可用串口的集合。
			/// @return
			///
			base::IDictionary<std::string, bsp::serial::ISerial *> const &SerialCollection();
		} // namespace serial
	} // namespace di
} // namespace bsp
