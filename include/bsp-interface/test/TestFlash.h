#pragma once
#include <array>
#include <bsp-interface/di/console.h>
#include <bsp-interface/di/delayer.h>
#include <bsp-interface/di/flash.h>
#include <bsp-interface/di/key.h>
#include <bsp-interface/di/led.h>

namespace bsp
{
	inline void TestFlash()
	{
		try
		{
			bsp::IFlash *flash = DI_FlashCollection().Get("internal-flash");
			std::array<uint32_t, 8> buffer{666, 2, 3};
			while (true)
			{
				DI_KeyScanner().ScanKeys();
				if (DI_KeyScanner().HasKeyDownEvent("key0"))
				{
					bsp::di::Console().WriteLine("检测到 key0 按下，开始操作");
					flash->EraseSector(1, 5);
					uint32_t value = flash->ReadUInt32(5, 0);
					if (value == static_cast<uint32_t>(-1))
					{
						bsp::di::Console().WriteLine("擦除成功");
					}

					flash->Program(5, 0, reinterpret_cast<uint8_t *>(buffer.data()));
					value = flash->ReadUInt32(5, 0);
					if (value == 666)
					{
						bsp::di::Console().WriteLine("编程成功");
					}
				}
			}
		}
		catch (std::exception const &e)
		{
			std::string str = e.what();
		}
	}
} // namespace bsp
