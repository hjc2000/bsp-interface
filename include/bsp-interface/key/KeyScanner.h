#pragma once
#include<boost/dynamic_bitset.hpp>
#include<bsp-interface/IDelayer.h>
#include<bsp-interface/key/IKey.h>
#include<bsp-interface/key/IKeyScanner.h>
#include<vector>

namespace bsp
{
	/// <summary>
	///		按键扫描器。
	///		* 板上的按键数量是固定的，所以初始化阶段构造一次本类对象就够了，
	///		  不要反复构造，析构，会造成内存碎片。因为本类用到了动态内存分配。
	/// </summary>
	class KeyScanner :public bsp::IKeyScanner
	{
	private:
		std::vector<IKey *> const &_keys;
		bsp::IDelayer &_delayer;

		boost::dynamic_bitset<> _last_scan_result;
		boost::dynamic_bitset<> _current_scan_result;

		boost::dynamic_bitset<> _key_down_events;
		boost::dynamic_bitset<> _key_up_events;
		boost::dynamic_bitset<> _key_pressed_events;

		boost::dynamic_bitset<> _no_delay_scan_result1;
		boost::dynamic_bitset<> _no_delay_scan_result2;

		void ScanKeysNoDelay(boost::dynamic_bitset<> &out);

	public:
		/// <summary>
		///		
		/// </summary>
		/// <param name="keys"></param>
		/// <param name="delayer">
		///		按键扫描需要延时消抖。
		/// </param>
		KeyScanner(std::vector<IKey *> const &keys, bsp::IDelayer &delayer);

		/// <summary>
		///		执行键盘扫描，更新内部状态。此函数应该被不断调用。
		/// </summary>
		void ScanKeys() override;

		bool HasKeyDownEvent(uint16_t key_index) override;
		bool HasKeyUpEvent(uint16_t key_index) override;
		bool HasKeyPressedEvent(uint16_t key_index) override;
	};
}
