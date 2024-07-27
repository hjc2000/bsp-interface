#pragma once
#include <boost/dynamic_bitset.hpp>
#include <bsp-interface/IDelayer.h>
#include <bsp-interface/di.h>
#include <bsp-interface/key/IKey.h>
#include <bsp-interface/key/IKeyScanner.h>
#include <vector>

namespace bsp
{
	/// @brief 按键扫描器。
	/// @note 板上的按键数量是固定的，所以初始化阶段构造一次本类对象就够了，
	/// 不要反复构造，析构，会造成内存碎片。因为本类用到了动态内存分配。
	class KeyScanner
		: public bsp::IKeyScanner
	{
	private:
		std::vector<IKey *> const &_keys;

		boost::dynamic_bitset<> _last_scan_result;
		boost::dynamic_bitset<> _current_scan_result;

		boost::dynamic_bitset<> _key_down_events;
		boost::dynamic_bitset<> _key_up_events;
		boost::dynamic_bitset<> _key_pressed_events;

		boost::dynamic_bitset<> _no_delay_scan_result1;
		boost::dynamic_bitset<> _no_delay_scan_result2;

		void ScanKeysNoDelay(boost::dynamic_bitset<> &out);

	public:
		KeyScanner(std::vector<IKey *> const &keys);

		/// @brief 执行键盘扫描，更新内部状态。此函数应该被不断调用。
		void ScanKeys() override;

		/// @brief 检测指定的按键是否有按下动作事件
		/// @note 所谓按下动作，就是从松开变成按下的这个状态变化。本事件只有在这个边沿会触发一次。
		/// @note 在再次调用 ScanKeys 之前，本函数的返回值会保持一致。
		/// @param key_index
		/// @return 指定的按键有按键按下动作则返回 true，否则返回 false。
		bool HasKeyDownEvent(uint16_t key_index) override;

		/// @brief 检测指定的按键是否有抬起动作事件。
		/// @note 所谓抬起动作，就是从按下变成松开的这个状态变化。本事件只有在这个边沿会触发一次。
		/// @note 在再次调用 ScanKeys 之前，本函数的返回值会保持一致。
		/// @param key_index
		/// @return 指定的按键有按键抬起动作则返回 true，否则返回 false。
		bool HasKeyUpEvent(uint16_t key_index) override;

		/// @brief 检测指定的按键是否有被按压着事件。
		/// @note 所谓被按压着事件，就是最近一次调用 ScanKeys 得到的按键状态。即当前扫描的结果
		/// 是按键正被按着。
		/// @param key_index
		/// @return 指定的按键正被按着则返回 true，否则返回 false。
		bool HasKeyPressedEvent(uint16_t key_index) override;
	};
}
