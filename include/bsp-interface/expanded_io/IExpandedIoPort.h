#pragma once
#include <base/stream/Span.h>
#include <bit>
#include <functional>
#include <stdint.h>
#include <string>

namespace bsp
{
	class IExpandedIoPort
	{
	public:
		/* #region 接口 */

		virtual std::string Name() const = 0;

		/// @brief 注册中断回调函数。
		/// @param func
		virtual void RegisterInterruptCallback(std::function<void()> func) = 0;

		/// @brief 取消注册中断回调函数。
		virtual void UnregisterInterruptCallback() = 0;

		/// @brief 读取一个字节。
		/// @param index 索引。要读取第几个字节。
		/// @return
		virtual uint8_t ReadByte(int index) = 0;

		/// @brief 写入一个字节。
		/// @param index 索引。要写入第几个字节。
		/// @param value
		virtual void WriteByte(int index, uint8_t value) = 0;

		/* #endregion */

		/// @brief 读取一个位。即读取指定索引的 IO 端子的电平。
		/// @param index IO 端子的索引。
		/// @return
		virtual bool ReadBit(int index)
		{
			uint8_t data = ReadByte(index / 8);
			uint8_t mask = 0x1 << (index % 8);
			return data & mask;
		}

		/// @brief 写 1 个位。即写指定索引的 IO 端子的电平。
		/// @param index IO 端子的索引。
		/// @param value IO 端子的电平。
		virtual void WriteBit(int index, bool value)
		{
			uint8_t byte = ReadByte(index / 8);
			uint8_t mask = 0x1 << (index % 8);
			if (value)
			{
				byte |= mask;
			}
			else
			{
				byte &= ~mask;
			}

			WriteByte(index / 8, byte);
		}

		/// @brief 翻转一个位。
		/// @param index
		virtual void ToggleBit(int index)
		{
			bool bit = ReadBit(index);
			WriteBit(index, !bit);
		}

		/// @brief 读取多个字节到 span 中。
		/// @param addr IO 端口中的字节的起始地址。
		/// @param span 读取到的字节被写入此 span.
		virtual void Read(int addr, base::Span const &span)
		{
			for (int i = 0; i < span.Size(); i++)
			{
				span[i] = ReadByte(addr + i);
			}
		}

		/// @brief 读取 IO 端口中指定索引处的一个 uint16_t 数据。
		/// @param index
		/// @return
		virtual uint16_t ReadUInt16(int index)
		{
			uint16_t data = 0;

			base::Span span{
				reinterpret_cast<uint8_t *>(&data),
				sizeof(data),
			};

			Read(index * 2, span);

			/* 刚才的操作方式是低字节放到数组的低索引处，这是小端序，
			 * 如果本机字节序是大端序，需要翻转。
			 */
			if (std::endian::native == std::endian::big)
			{
				span.Reverse();
			}

			return data;
		}

		/// @brief 读取 IO 端口中指定索引处的一个 uint32_t 数据。
		/// @param index
		/// @return
		virtual uint32_t ReadUInt32(int index)
		{
			uint32_t data = 0;

			base::Span span{
				reinterpret_cast<uint8_t *>(&data),
				sizeof(data),
			};

			Read(index * 2, span);

			/* 刚才的操作方式是低字节放到数组的低索引处，这是小端序，
			 * 如果本机字节序是大端序，需要翻转。
			 */
			if (std::endian::native == std::endian::big)
			{
				span.Reverse();
			}

			return data;
		}

		/// @brief 读取 IO 端口中指定索引处的一个 uint64_t 数据。
		/// @param index
		/// @return
		virtual uint64_t ReadUInt64(int index)
		{
			uint64_t data = 0;

			base::Span span{
				reinterpret_cast<uint8_t *>(&data),
				sizeof(data),
			};

			Read(index * 2, span);

			/* 刚才的操作方式是低字节放到数组的低索引处，这是小端序，
			 * 如果本机字节序是大端序，需要翻转。
			 */
			if (std::endian::native == std::endian::big)
			{
				span.Reverse();
			}

			return data;
		}
	};
} // namespace bsp
