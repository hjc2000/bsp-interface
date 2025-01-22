#pragma once
#include <bsp-interface/sdram/ISDRAM.h>
#include <bsp-interface/sdram/ISDRAMController.h>

namespace bsp
{
	namespace sdram
	{
		namespace chip
		{
			/// @brief 帮助通过 bsp::ISDRAMController 初始化 W9825G6KH_6 SDRAM 芯片。
			class W9825G6KH_6 :
				bsp::sdram::ISDRAM
			{
			private:
				bsp::sdram::ISDRAMController &_controller;

			public:
				/// @brief 构造函数。
				/// @param controller 需要一个控制器来控制 SDRAM 芯片。
				W9825G6KH_6(bsp::sdram::ISDRAMController &controller);

				/// @brief 打开 SDRAM.
				/// @note 分为 2 步：
				/// 	@li 打开 SDRAM 控制器。
				/// 	@li 初始化 SDRAM 芯片。
				virtual void Open() override;

				/// @brief 此 SDRAM 的内存段。
				/// @return
				virtual base::Span Span() const override;
			};
		} // namespace chip
	} // namespace sdram
} // namespace bsp
