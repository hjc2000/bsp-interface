#pragma once
#include <base/LockGuard.h>
#include <cstddef>
#include <stdint.h>

namespace bsp
{
	class IFlash
		: public base::ILock
	{
	public:
		/// @brief flash 的最小编程单位。单位：字节。
		/// @note 最小单位是一次编程必须写入这么多字节，即使要写入的数据没有这么多，在一次
		/// 写入后，整个单位大小的区域都无法再次写入了，除非擦除整个扇区。
		/// @return 返回此 flash 编程的最小单位。
		virtual int32_t MinProgrammingUnit() = 0;

		/// @brief flash 的地址需要对齐到的字节数。本类中其他方法，凡事要传入 flash 地址的，
		/// 都需要对齐到本属性。
		/// @return
		virtual int32_t FlashAddressAlign() = 0;

		/// @brief 擦除一整个 bank。
		/// @param bank_id 要擦除的扇区的 id。例如要擦除 bank1，就传入 1，要擦除 bank2 就传入 2.
		virtual void EraseBank(int32_t bank_id) = 0;

		/// @brief 擦除指定 bank 中从 start_sector_index 开始的 sector_count 个扇区。
		/// @param bank_id 要擦除的扇区所在的 bank 的 id。
		/// @param start_sector_index 要擦除的扇区的起始索引。
		/// @param sector_count 要擦除的扇区的数量。
		virtual void EraseSector(int32_t bank_id, int32_t start_sector_index, int32_t sector_count) = 0;

		/// @brief 将 flash 的数据读取到缓冲区中
		/// @param bank_id
		/// @param addr
		/// @param buffer
		/// @param count
		virtual void ReadBuffer(int32_t bank_id, size_t addr, uint8_t *buffer, int32_t count) = 0;

		/// @brief 编程
		/// @param bank_id 要写入的 bank 的 id.
		/// @param addr 要写入的数据相对于此 bank 的起始地址的地址。
		/// @param buffer 要写入到 flash 的数据所在的缓冲区。
		/// @warning buffer 的元素个数必须 >= MinProgrammingUnit，否则将发生内存访问越界。
		virtual void Program(int32_t bank_id, size_t addr, uint32_t const *buffer) = 0;

		/// @brief 读取指定 bank 的指定地址的 1 字节数据。
		/// @param bank_id bank 的 id。例如 bank1 的 id 是 1.
		/// @param addr 相对于此 bank 的起始地址的地址。
		/// @return
		uint8_t ReadUInt8(int32_t bank_id, size_t addr);
		uint16_t ReadUInt16(int32_t bank_id, size_t addr);
		uint32_t ReadUInt32(int32_t bank_id, size_t addr);
		uint64_t ReadUInt64(int32_t bank_id, size_t addr);
	};
}
