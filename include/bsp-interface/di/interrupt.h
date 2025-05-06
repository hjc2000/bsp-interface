#pragma once
#include "bsp-interface/interrupt/IExtiManager.h"
#include "bsp-interface/interrupt/IIsrManager.h"

namespace bsp
{
	namespace di
	{
		namespace interrupt
		{
			///
			/// @brief 外部中断管理器。
			///
			/// @return
			///
			bsp::IExtiManager &ExtiManager();

			///
			/// @brief 中断管理器。
			///
			/// @note 此依赖本库已经提供了，不需要实现此函数了。
			///
			/// @return
			///
			bsp::IIsrManager &IsrManager();

		} // namespace interrupt
	} // namespace di
} // namespace bsp
