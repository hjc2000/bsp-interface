#include "di.h"
#include <base/Initializer.h>

/// @brief 一个翻译单元只需要注册一个初始化器就行了
static base::Initializer _initializer{
	[]()
	{
		bsp::IsrManager::Instance();
	}};

bsp::IsrManager &DI_IsrManager()
{
	return bsp::IsrManager::Instance();
}
