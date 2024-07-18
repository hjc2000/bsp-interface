#include "IFlash.h"
#include <stdexcept>

size_t bsp::IFlash::GetAbsoluteAddress(int32_t bank_id, size_t addr)
{
	if (addr >= GetBankSize(bank_id))
	{
		throw std::out_of_range{"地址超出范围"};
	}

	return GetBankBaseAddress(bank_id) + addr;
}

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
