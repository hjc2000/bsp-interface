#pragma once
#include <array>
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

		virtual void ReadBuffer(int32_t bank_id, size_t addr, uint8_t *buffer, int32_t count) = 0;

		/// @brief 编程
		/// @param bank_id 要写入的 bank 的 id.
		///
		/// @param addr 要写入的数据相对于此 bank 的起始地址的地址。
		/// @warning 此地址要 32 字节对齐。
		///
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
