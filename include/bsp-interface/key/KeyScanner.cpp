#include "KeyScanner.h"
#include <bsp-interface/di/key.h>

using namespace bsp;

void KeyScanner::ScanKeysNoDelay(std::map<std::string, bool> &out)
{
    for (auto key : DI_KeyCollection())
    {
        out[key->KeyName()] = key->KeyIsDown();
    }
}

void KeyScanner::ScanKeys()
{
    _last_scan_result = _current_scan_result;
    ScanKeysNoDelay(_no_delay_scan_result1);
    DI_Delayer().Delay(std::chrono::milliseconds{10});
    ScanKeysNoDelay(_no_delay_scan_result2);

    for (auto key : DI_KeyCollection())
    {
        _current_scan_result[key->KeyName()] = _no_delay_scan_result1[key->KeyName()] &&
                                               _no_delay_scan_result2[key->KeyName()];
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
