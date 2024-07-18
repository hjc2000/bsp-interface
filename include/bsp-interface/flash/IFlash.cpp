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

void bsp::IFlash::EraseSector(int32_t bank_id, int32_t start_sector_index, int32_t sector_count)
{
	/* HAL 库中虽然也有连续擦除几个扇区的功能，但是，使用 HAL 库，每擦除 1 个扇区他都会触发一次中断，
	 * 回调 HAL_FLASH_EndOfOperationCallback 函数。也即一次调用却对应着多次回调。这会给信号量的使用
	 * 带来麻烦，所以就实现为利用
	 * 		virtual void EraseSector(int32_t bank_id, int32_t sector_index) = 0;
	 * 通过循环中多次调用，一个个扇区擦除来实现连续擦除。
	 *
	 * 这不会有性能问题，因为 HAL 库其实也是在循环中一个个扇区擦除的。
	 */
	if (start_sector_index + sector_count > GetBankSectorCount(bank_id))
	{
		throw std::out_of_range{"要擦除的扇区超出实际范围"};
	}

	for (int32_t i = 0; i < sector_count; i++)
	{
		EraseSector(bank_id, start_sector_index + i);
	}
}
