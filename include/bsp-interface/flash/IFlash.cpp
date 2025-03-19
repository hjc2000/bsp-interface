#include "IFlash.h"
#include <stdexcept>

void bsp::IFlash::EraseSector(int32_t start_sector_index, int32_t sector_count)
{
	/* HAL 库中虽然也有连续擦除几个扇区的功能，但是，使用 HAL 库，每擦除 1 个扇区他都会触发一次中断，
	 * 回调 HAL_FLASH_EndOfOperationCallback 函数。也即一次调用却对应着多次回调。这会给信号量的使用
	 * 带来麻烦，所以就实现为利用
	 * 		virtual void EraseSector(int32_t bank_index, int32_t sector_index) = 0;
	 * 通过循环中多次调用，一个个扇区擦除来实现连续擦除。
	 *
	 * 这不会有性能问题，因为 HAL 库其实也是在循环中一个个扇区擦除的。
	 */
	if (start_sector_index + sector_count > SectorCount())
	{
		throw std::out_of_range{"要擦除的扇区超出实际范围"};
	}

	for (int32_t i = 0; i < sector_count; i++)
	{
		EraseSector(start_sector_index + i);
	}
}

void bsp::IFlash::Program(int32_t sector_index, size_t addr, uint8_t const *buffer)
{
	Program(SectorSize() * sector_index + addr, buffer);
}

#pragma region 读取

void bsp::IFlash::Read(int32_t sector_index, size_t addr, uint8_t *buffer, int32_t count)
{
	Read(SectorSize() * sector_index + addr, buffer, count);
}

uint8_t bsp::IFlash::ReadUInt8(size_t addr)
{
	uint8_t ret;
	Read(addr, reinterpret_cast<uint8_t *>(&ret), sizeof(ret));
	return ret;
}

uint8_t bsp::IFlash::ReadUInt8(int32_t sector_index, size_t addr)
{
	return ReadUInt8(SectorSize() * sector_index + addr);
}

uint16_t bsp::IFlash::ReadUInt16(size_t addr)
{
	uint16_t ret;
	Read(addr, reinterpret_cast<uint8_t *>(&ret), sizeof(ret));
	return ret;
}

uint16_t bsp::IFlash::ReadUInt16(int32_t sector_index, size_t addr)
{
	return ReadUInt16(SectorSize() * sector_index + addr);
}

uint32_t bsp::IFlash::ReadUInt32(size_t addr)
{
	uint32_t ret;
	Read(addr, reinterpret_cast<uint8_t *>(&ret), sizeof(ret));
	return ret;
}

uint32_t bsp::IFlash::ReadUInt32(int32_t sector_index, size_t addr)
{
	return ReadUInt32(SectorSize() * sector_index + addr);
}

uint64_t bsp::IFlash::ReadUInt64(size_t addr)
{
	uint64_t ret;
	Read(addr, reinterpret_cast<uint8_t *>(&ret), sizeof(ret));
	return ret;
}

uint64_t bsp::IFlash::ReadUInt64(int32_t sector_index, size_t addr)
{
	return ReadUInt64(SectorSize() * sector_index + addr);
}

#pragma endregion
