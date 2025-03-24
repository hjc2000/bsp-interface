#include "KeyScanner.h"
#include "base/task/delay.h"
#include <bsp-interface/di/key.h>

using namespace bsp;

void KeyScanner::ScanKeysNoDelay(std::map<std::string, bool> &out)
{
	for (auto &pair : bsp::di::key::KeyCollection())
	{
		out[pair.second->KeyName()] = pair.second->KeyIsDown();
	}
}

void KeyScanner::ScanKeys()
{
	_last_scan_result = _current_scan_result;
	ScanKeysNoDelay(_no_delay_scan_result1);
	base::Delay(std::chrono::milliseconds{10});
	ScanKeysNoDelay(_no_delay_scan_result2);
	for (auto &pair : bsp::di::key::KeyCollection())
	{
		_current_scan_result[pair.second->KeyName()] = _no_delay_scan_result1[pair.second->KeyName()] &&
													   _no_delay_scan_result2[pair.second->KeyName()];
	}
}

bool KeyScanner::HasKeyDownEvent(std::string key_name)
{
	return _current_scan_result[key_name] && (!_last_scan_result[key_name]);
}

bool KeyScanner::HasKeyUpEvent(std::string key_name)
{
	return (!_current_scan_result[key_name]) && _last_scan_result[key_name];
}

bool KeyScanner::HasKeyPressedEvent(std::string key_name)
{
	return _current_scan_result[key_name];
}
