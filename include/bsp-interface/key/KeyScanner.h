#pragma once
#include <boost/dynamic_bitset.hpp>
#include <bsp-interface/IDelayer.h>
#include <bsp-interface/di.h>
#include <bsp-interface/key/IKey.h>
#include <bsp-interface/key/IKeyScanner.h>

namespace bsp
{
	/// @brief 按键扫描器。
	/// @note 板上的按键数量是固定的，所以初始化阶段构造一次本类对象就够了，
	/// 不要反复构造，析构，会造成内存碎片。因为本类用到了动态内存分配。
	/// @note 要求调用一次本函数后，内部储存扫描结果，接下来无论多少次检查按键事件，
	/// 结果都一样，即检查事件的函数是幂等的。只有再次调用本函数，按键事件的有无
	/// 才会被更新。
	class KeyScanner
		: public bsp::IKeyScanner
	{
	private:
		base::IReadOnlyCollection<int, bsp::IKey *> const &_key_collection;

		boost::dynamic_bitset<> _last_scan_result;
		boost::dynamic_bitset<> _current_scan_result;

		boost::dynamic_bitset<> _key_down_events;
		boost::dynamic_bitset<> _key_up_events;
		boost::dynamic_bitset<> _key_pressed_events;

		boost::dynamic_bitset<> _no_delay_scan_result1;
		boost::dynamic_bitset<> _no_delay_scan_result2;

		void ScanKeysNoDelay(boost::dynamic_bitset<> &out);

	public:
		KeyScanner(base::IReadOnlyCollection<int, bsp::IKey *> const &key_collection);

		void ScanKeys() override;
		bool HasKeyDownEvent(int key_index) override;
		bool HasKeyUpEvent(int key_index) override;
		bool HasKeyPressedEvent(int key_index) override;
	};
}
