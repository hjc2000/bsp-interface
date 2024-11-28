#pragma once
#include <base/LockGuard.h>
#include <cstddef>
#include <stdint.h>
#include <string>

namespace bsp
{
    /// @brief flash 接口。
    class IFlash :
        public base::ILock
    {
    public:
        /// @brief flash 的名称。
        /// @return
        virtual std::string Name() = 0;

#pragma region flash 参数
        /// @brief 一个扇区的大小。单位：字节。
        /// @return
        virtual size_t SectorSize() const = 0;

        /// @brief 扇区数量。
        /// @return
        virtual int32_t SectorCount() const = 0;

        /// @brief flash 的最小编程单位。单位：字节。
        /// @note 最小单位是一次编程必须写入这么多字节，即使要写入的数据没有这么多，在一次
        /// 写入后，整个单位大小的区域都无法再次写入了，除非擦除整个扇区。
        /// @return 返回此 flash 编程的最小单位。
        virtual int32_t MinProgrammingUnit() const = 0;
#pragma endregion

#pragma region 擦除
        /// @brief 擦除整个 flash.
        virtual void Erase() = 0;

        /// @brief 擦除指定扇区。
        /// @param sector_index 要擦除的扇区索引。
        virtual void EraseSector(int32_t sector_index) = 0;

        /// @brief 擦除从 start_sector_index 开始的 sector_count 个扇区。
        /// @param start_sector_index 要擦除的扇区的起始索引。
        /// @param sector_count 要擦除的扇区的数量。
        void EraseSector(int32_t start_sector_index, int32_t sector_count);
#pragma endregion

#pragma region 编程
        /// @brief 编程
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
        virtual void Program(size_t addr, uint8_t const *buffer) = 0;

        /// @brief 编程。
        ///
        /// @param sector_index 扇区索引。
        ///
        /// @param addr 相对于此扇区的地址。
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
        void Program(int32_t sector_index, size_t addr, uint8_t const *buffer)
        {
            Program(SectorSize() * sector_index + addr, buffer);
        }

#pragma endregion

#pragma region 读取
        /// @brief 将 flash 的数据读取到缓冲区中
        /// @param addr 相对于此 bank 的起始地址的地址。
        /// @param buffer 读出的数据放到此缓冲区。
        /// @param count 要读取的字节数。
        virtual void Read(size_t addr, uint8_t *buffer, int32_t count) = 0;

        /// @brief 将 flash 的数据读取到缓冲区中。
        /// @param sector_index 相对于此 bank 的扇区索引。
        /// @param addr 相对于此扇区的地址。
        /// @param buffer 将 flash 中的数据读到该缓冲区中。
        /// @param count 要读取的字节数。
        void Read(int32_t sector_index, size_t addr, uint8_t *buffer, int32_t count)
        {
            Read(SectorSize() * sector_index + addr, buffer, count);
        }

        /// @brief 读取指定地址的 1 字节数据。
        /// @param addr 相对于此 bank 的起始地址的地址。
        /// @return
        uint8_t ReadUInt8(size_t addr);

        /// @brief 读取指定地址的 1 字节数据。
        /// @param sector_index 扇区索引。
        /// @param addr 相对于该扇区的地址。
        /// @return
        uint8_t ReadUInt8(int32_t sector_index, size_t addr)
        {
            return ReadUInt8(SectorSize() * sector_index + addr);
        }

        /// @brief 读取指定 bank 的指定地址的 2 字节数据。
        /// @param addr 相对于此 bank 的起始地址的地址。
        /// @return
        uint16_t ReadUInt16(size_t addr);

        /// @brief 读取指定 bank 的指定地址的 2 字节数据。
        /// @param sector_index 扇区索引。
        /// @param addr 相对于该扇区的地址。
        /// @return
        uint16_t ReadUInt16(int32_t sector_index, size_t addr)
        {
            return ReadUInt16(SectorSize() * sector_index + addr);
        }

        /// @brief 读取指定 bank 的指定地址的 4 字节数据。
        /// @param addr 相对于此 bank 的起始地址的地址。
        /// @return
        uint32_t ReadUInt32(size_t addr);

        /// @brief 读取指定 bank 的指定地址的 4 字节数据。
        /// @param sector_index 扇区索引。
        /// @param addr 相对于该扇区的地址。
        /// @return
        uint32_t ReadUInt32(int32_t sector_index, size_t addr)
        {
            return ReadUInt32(SectorSize() * sector_index + addr);
        }

        /// @brief 读取指定 bank 的指定地址的 8 字节数据。
        /// @param addr 相对于此 bank 的起始地址的地址。
        /// @return
        uint64_t ReadUInt64(size_t addr);

        /// @brief 读取指定 bank 的指定地址的 8 字节数据。
        /// @param sector_index 扇区索引。
        /// @param addr 相对于该扇区的地址。
        /// @return
        uint64_t ReadUInt64(int32_t sector_index, size_t addr)
        {
            return ReadUInt64(SectorSize() * sector_index + addr);
        }

#pragma endregion
    };
} // namespace bsp
