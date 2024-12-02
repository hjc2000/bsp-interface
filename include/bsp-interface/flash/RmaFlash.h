#pragma once
#include <base/stream/Span.h>
#include <bsp-interface/flash/IFlash.h>

namespace bsp
{
    /// @brief 基于 RAM 的虚拟 flash.
    class RmaFlash :
        public bsp::IFlash
    {
    private:
        std::string _name;
        base::Span _span;

    public:
        /// @brief 构造一个基于 RAM 的虚拟 flash.
        /// @param name flash 名称。
        /// @param span 在此内存段上虚拟出一个 flash.
        RmaFlash(std::string const &name, base::Span const &span);

#pragma region flash 信息，规格参数
        /// @brief flash 的名称。
        /// @return
        std::string Name() override;

        /// @brief 一个扇区的大小。单位：字节。
        /// @note 擦除必须以扇区为单位，至少擦除一个扇区。
        /// @return
        size_t SectorSize() const override;

        /// @brief 扇区数量。
        /// @return
        int32_t SectorCount() const override;

        /// @brief flash 的最小编程单位。单位：字节。
        /// @note 最小单位是一次编程必须写入这么多字节，即使要写入的数据没有这么多，在一次
        /// 写入后，整个单位大小的区域都无法再次写入了，除非擦除整个扇区。
        /// @return 返回此 flash 编程的最小单位。
        int32_t ProgrammingSize() const override;
#pragma endregion

#pragma region 擦除
        /// @brief 擦除整个 flash.
        void Erase() override;

        /// @brief 擦除指定扇区。
        /// @param sector_index 要擦除的扇区索引。
        void EraseSector(int32_t sector_index) override;
        using bsp::IFlash::EraseSector;
#pragma endregion

#pragma region 编程
        /// @brief 编程
        ///
        /// @param addr 要写入的数据在此 flash 中的地址。
        /// @note 此地址必须能被 ProgrammingSize 整除。
        ///
        /// @param buffer 要写入到 flash 的数据所在的缓冲区。大小为 ProgrammingSize。
        /// @note 底层在编程时，会读取并且只会读取 ProgrammingSize 个字节。
        /// @warning buffer 的字节数必须 >= ProgrammingSize ，否则因为底层无论如何都会读取
        /// ProgrammingSize 个字节，将会发生内存访问越界。
        /// @note 不同平台对 buffer 有对齐要求。例如 stm32 的 HAL 要求 buffer 要 4 字节
        /// 对齐。这里使用 uint8_t const * ，接口的实现者自己计算 buffer 能否被对齐字节数整除，
        /// 不能整除抛出异常。
        /// @note 对于 4 字节对齐的情况，调用者可以创建 uint32_t 数组，然后
        /// 将 uint32_t const * 强制转换为 uint8_t const * 作为 buffer 传进来。
        void Program(size_t addr, uint8_t const *buffer) override;
        using bsp::IFlash::Program;
#pragma endregion

#pragma region 读取
        /// @brief 将 flash 的数据读取到缓冲区中
        /// @param addr 在此 flash 中的地址。
        /// @param buffer 读出的数据放到此缓冲区。
        /// @param count 要读取的字节数。
        ///
        /// @note 实现者需要将本函数实现为支持单字节读取。如果硬件不支持，可以自己准备一个足够大的数组，
        /// 读取完后再将小于读取单位的字节数拷贝到 buffer 中。
        void Read(size_t addr, uint8_t *buffer, int32_t count) override;
        using bsp::IFlash::Read;
#pragma endregion
    };
} // namespace bsp
