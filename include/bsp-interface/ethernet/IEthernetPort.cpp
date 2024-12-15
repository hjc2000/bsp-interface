#include "IEthernetPort.h"

void bsp::IEthernetPort::EnableAutoNegotiation()
{
	uint32_t bcr = ReadPHYRegister(0);
	bcr |= 0x1000U;
	WritePHYRegister(0, bcr);
}
