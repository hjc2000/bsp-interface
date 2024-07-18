#include "IFlash.h"

uint8_t bsp::IFlash::ReadUInt8(int32_t bank_id, size_t addr)
{
	uint8_t ret;
	ReadBuffer(bank_id, addr, reinterpret_cast<uint8_t *>(&ret), sizeof(ret));
	return ret;
}

uint16_t bsp::IFlash::ReadUInt16(int32_t bank_id, size_t addr)
{
	uint16_t ret;
	ReadBuffer(bank_id, addr, reinterpret_cast<uint8_t *>(&ret), sizeof(ret));
	return ret;
}

uint32_t bsp::IFlash::ReadUInt32(int32_t bank_id, size_t addr)
{
	uint32_t ret;
	ReadBuffer(bank_id, addr, reinterpret_cast<uint8_t *>(&ret), sizeof(ret));
	return ret;
}

uint64_t bsp::IFlash::ReadUInt64(int32_t bank_id, size_t addr)
{
	uint64_t ret;
	ReadBuffer(bank_id, addr, reinterpret_cast<uint8_t *>(&ret), sizeof(ret));
	return ret;
}
