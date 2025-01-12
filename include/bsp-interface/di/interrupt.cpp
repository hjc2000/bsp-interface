#include "interrupt.h"
#include <IsrManager.h>

namespace
{
	/// @brief 因为不依赖其他全局单例，所以就直接定义成全局对象了。
	/// 另外，还可以避免定义成非全局对象时，中断服务函数和主程序同时构造对象。
	bsp::IsrManager _isr_manager;
} // namespace

bsp::IIsrManager &DI_IsrManager()
{
	return _isr_manager;
}
