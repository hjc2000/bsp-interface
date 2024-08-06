#include "KeyScanner.h"

using namespace bsp;

void KeyScanner::ScanKeysNoDelay(boost::dynamic_bitset<> &out)
{
	int i = 0;
	for (auto key : DI_KeyCollection())
	{
		out[i] = key->KeyIsDown();
		i++;
	}
}

KeyScanner::KeyScanner()
	: _last_scan_result(DI_KeyCollection().Count()),
	  _current_scan_result(DI_KeyCollection().Count()),

	  _key_down_events(DI_KeyCollection().Count()),
	  _key_up_events(DI_KeyCollection().Count()),
	  _key_pressed_events(DI_KeyCollection().Count()),

	  _no_delay_scan_result1(DI_KeyCollection().Count()),
	  _no_delay_scan_result2(DI_KeyCollection().Count())
{
}

void KeyScanner::ScanKeys()
{
	ScanKeysNoDelay(_no_delay_scan_result1);
	DI_Delayer().Delay(std::chrono::milliseconds{10});
	ScanKeysNoDelay(_no_delay_scan_result2);
	_current_scan_result = _no_delay_scan_result1 & _no_delay_scan_result2;

	// 更新事件状态
	_key_down_events = (~_last_scan_result) & _current_scan_result;
	_key_up_events = _last_scan_result & (~_current_scan_result);
	_key_pressed_events = _current_scan_result;
	_last_scan_result = _current_scan_result;
}

bool KeyScanner::HasKeyDownEvent(int key_index)
{
	if (key_index >= DI_KeyCollection().Count())
	{
		return false;
	}

	return _key_down_events[key_index];
}

bool KeyScanner::HasKeyUpEvent(int key_index)
{
	if (key_index >= DI_KeyCollection().Count())
	{
		return false;
	}

	return _key_up_events[key_index];
}

bool KeyScanner::HasKeyPressedEvent(int key_index)
{
	if (key_index >= DI_KeyCollection().Count())
	{
		return false;
	}

	return _key_pressed_events[key_index];
}
