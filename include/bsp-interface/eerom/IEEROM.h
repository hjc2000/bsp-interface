#pragma once
#include <base/stream/ReadOnlySpan.h>
#include <stdint.h>
#include <string>

namespace bsp
{
    /// @brief EEROM 接口
    class IEEROM
    {
    public:
        /// @brief EEROM 的名称。
        /// @return
        virtual std::string Name() const = 0;

        /// @brief EEROM 的容量。单位：字节。
        /// @return
        virtual int32_t Size() const = 0;

        /// @brief 读取 1 个字节的数据。
        /// @param addr 数据地址。
        /// @return 读取到的字节。
        virtual uint8_t ReadByte(int32_t addr) = 0;

        /// @brief 读取 uint16_t.
        /// @param addr
        /// @return
        uint16_t ReadUInt16(int32_t addr);

        /// @brief 读取 uint32_t.
        /// @param addr
        /// @return
        uint32_t ReadUInt32(int32_t addr);

        /// @brief 读取 uint64_t.
        /// @param addr
        /// @return
        uint64_t ReadUInt64(int32_t addr);

        /// @brief 连续将 EEROM 的一段区域读取到 span 中。
        /// @param addr
        /// @param span
        virtual void Read(int32_t addr, base::Span const &span);

        /// @brief 连续将 EEROM 的一段区域读取到 buffer 中。
        /// @param addr
        /// @param buffer
        /// @param offset
        /// @param count
        void Read(int32_t addr, uint8_t *buffer, int32_t offset, int32_t count);

        /// @brief 写 1 个字节的数据。
        /// @param addr 数据地址。
        /// @param data 数据。
        virtual void WriteByte(int32_t addr, uint8_t data) = 0;

        /// @brief 写入 uint16_t.
        /// @param addr
        /// @param data
        void WriteUInt16(int32_t addr, uint16_t data);

        /// @brief 写入 uint32_t.
        /// @param addr
        /// @param data
        void WriteUInt32(int32_t addr, uint32_t data);

        /// @brief 写入 uint64_t.
        /// @param addr
        /// @param data
        void WriteUInt64(int32_t addr, uint64_t data);

        /// @brief 将 span 写入 EEROM 的 addr 开始的连续区域。
        /// @param addr
        /// @param span
        virtual void Write(int32_t addr, base::ReadOnlySpan const &span);

        /// @brief 将 buffer 写入 EEROM 的 addr 开始的连续区域。
        /// @param addr
        /// @param buffer
        /// @param offset
        /// @param count
        void Write(int32_t addr, uint8_t const *buffer, int32_t offset, int32_t count);
    };
} // namespace bsp
