#pragma once
#include <base/LockGuard.h>
#include <cstddef>
#include <stdint.h>
#include <string>

namespace bsp
{
    class IFlash :
        public base::ILock
    {
    public:
        /// @brief flash 的名称。
        /// @return
        virtual std::string Name() = 0;

        /// @brief 获取此 flash 的 bank 数量。
        /// @return
        virtual int32_t BankCount() const = 0;

        /// @brief 获取指定 bank 的扇区数量。
        /// @param bank_index
        /// @return
        virtual int32_t GetBankSectorCount(int32_t bank_index) const = 0;

        /// @brief 获取指定 bank 的基地址。
        /// @param bank_index
        /// @return
        virtual size_t GetBankBaseAddress(int32_t bank_index) const = 0;

        /// @brief 获取指定 bank 的大小。单位：字节。
        /// @param bank_index
        /// @return
        virtual size_t GetBankSize(int32_t bank_index) const = 0;

        /// @brief 将相对于指定 bank 的起始地址的地址转化为绝对地址。
        /// @param bank_index
        /// @param addr 相对于此 bank 起始地址的地址。
        /// @return 绝对地址。可以被强制转换为指针。
        size_t GetAbsoluteAddress(int32_t bank_index, size_t addr) const;

        /// @brief flash 的最小编程单位。单位：字节。
        /// @note 最小单位是一次编程必须写入这么多字节，即使要写入的数据没有这么多，在一次
        /// 写入后，整个单位大小的区域都无法再次写入了，除非擦除整个扇区。
        /// @return 返回此 flash 编程的最小单位。
        virtual int32_t MinProgrammingUnit() const = 0;

        /// @brief 擦除一整个 bank。
        /// @param bank_index
        virtual void EraseBank(int32_t bank_index) = 0;

        /// @brief 擦除指定 bank 的指定扇区。
        /// @param bank_index
        /// @param sector_index 要擦除的扇区索引。
        virtual void EraseSector(int32_t bank_index, int32_t sector_index) = 0;

        /// @brief 擦除指定 bank 中从 start_sector_index 开始的 sector_count 个扇区。
        /// @param bank_index
        /// @param start_sector_index 要擦除的扇区的起始索引。
        /// @param sector_count 要擦除的扇区的数量。
        void EraseSector(int32_t bank_index, int32_t start_sector_index, int32_t sector_count);

        /// @brief 将 flash 的数据读取到缓冲区中
        /// @param bank_index
        /// @param addr 相对于此 bank 的起始地址的地址。
        /// @param buffer 读出的数据放到此缓冲区。
        /// @param count 要读取的字节数。
        virtual void ReadBuffer(int32_t bank_index, size_t addr, uint8_t *buffer, int32_t count) = 0;

        /// @brief 编程
        /// @param bank_index
        ///
        /// @param addr 要写入的数据相对于此 bank 的起始地址的地址。
        /// @note 此地址必须能被 MinProgrammingUnit 整除。
        ///
        /// @param buffer 要写入到 flash 的数据所在的缓冲区。大小为 MinProgrammingUnit。
        /// @note 底层在编程时，会读取并且只会读取 MinProgrammingUnit 个字节。
        /// @warning buffer 的字节数必须 >= MinProgrammingUnit ，否则因为底层无论如何都会读取
        /// MinProgrammingUnit 个字节，所以将发生内存访问越界。
        /// @note 不同平台对 buffer 有对齐要求。例如 stm32 的 HAL 要求 buffer 要 4 字节
        /// 对齐。这里使用 uint8_t const * ，接口的实现者自己计算 buffer 能否被对齐字节数整除，
        /// 不能整除抛出异常。
        /// @note 对于 4 字节对齐的情况，调用者可以创建 uint32_t 数组，然后
        /// 将 uint32_t const * 强制转换为 uint8_t const * 作为 buffer 传进来。
        virtual void Program(int32_t bank_index, size_t addr, uint8_t const *buffer) = 0;

#pragma region 读取
        /// @brief 读取指定 bank 的指定地址的 1 字节数据。
        /// @param bank_index
        /// @param addr 相对于此 bank 的起始地址的地址。
        /// @return
        uint8_t ReadUInt8(int32_t bank_index, size_t addr);

        /// @brief 读取指定 bank 的指定地址的 2 字节数据。
        /// @param bank_index
        /// @param addr 相对于此 bank 的起始地址的地址。
        /// @return
        uint16_t ReadUInt16(int32_t bank_index, size_t addr);

        /// @brief 读取指定 bank 的指定地址的 4 字节数据。
        /// @param bank_index
        /// @param addr 相对于此 bank 的起始地址的地址。
        /// @return
        uint32_t ReadUInt32(int32_t bank_index, size_t addr);

        /// @brief 读取指定 bank 的指定地址的 8 字节数据。
        /// @param bank_index
        /// @param addr 相对于此 bank 的起始地址的地址。
        /// @return
        uint64_t ReadUInt64(int32_t bank_index, size_t addr);
#pragma endregion
    };
} // namespace bsp
