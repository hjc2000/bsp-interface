#pragma once
#include <bsp-interface/key/IKey.h>
#include <stdint.h>

namespace bsp
{
	/// @brief 按键扫描器接口
	/// @note 要求调用一次本函数后，内部储存扫描结果，接下来无论多少次检查按键事件，
	/// 结果都一样，即检查事件的函数是幂等的。只有再次调用本函数，按键事件的有无
	/// 才会被更新。
	class IKeyScanner
	{
	public:
		/// @brief 扫描按键
		/// @note 此函数需要被循环调用，这样才能扫描到按键事件。
		virtual void ScanKeys() = 0;

		virtual bool HasKeyDownEvent(uint16_t key_index) = 0;
		virtual bool HasKeyUpEvent(uint16_t key_index) = 0;
		virtual bool HasKeyPressedEvent(uint16_t key_index) = 0;
	};
}
