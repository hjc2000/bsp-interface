#include"ISerial.h"

uint64_t bsp::ISerial::BaudTicks(uint32_t baud_count, uint32_t tick_freq)
{
	/*
	* baud_interval = 1 / baud_rate
	* tick_interval = 1 / tick_frequency
	*
	* tick_count = baud_count * baud_interval / tick_interval
	* tick_count = baud_count * (1 / baud_rate) / (1 / tick_frequency)
	* tick_count = baud_count * (1 / baud_rate) * tick_frequency
	* tick_count = baud_count * tick_frequency / baud_rate
	*/

	uint64_t tick_count = baud_count * tick_freq / BaudRate();
	return tick_count;
}
