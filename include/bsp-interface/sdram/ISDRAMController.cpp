#include "ISDRAMController.h"

void bsp::sdram::ISDRAMController::AutoRefresh(int refresh_times)
{
	for (int i = 0; i < refresh_times; i++)
	{
		AutoRefresh();
	}
}
