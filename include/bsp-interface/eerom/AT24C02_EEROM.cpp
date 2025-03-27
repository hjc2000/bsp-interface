#include "AT24C02_EEROM.h"
#include "base/task/delay.h"

bsp::AT24C02_EEROM::AT24C02_EEROM(std::string const &name, bsp::IIicHost *host)
{
	/* IIC 设备类不能自己去调用 IIicHost 的打开方法或初始化方法，因为一个 IIicHost
	 * 对象可能给多个 IIC 设备类对象共用，如果每个 IIC 设备类对象都要 Open 一次，那就
	 * 乱套了。而且 IIC 接口各种各样，可能有很多 Open 的重载版本和初始化方式。
	 *
	 * 综上，Open 的工作应该在 IIC 设备类外部完成。
	 */

	_name = name;
	_iic_host = host;

	/* 虽然 IIC 设备类不能调用 IIicHost 的 Open 方法，但是还是需要一些途径来改变 IIicHost
	 * 的时钟频率、等待超时周期数。因为每个 IIC 设备类都有自己的响应速度上限。
	 */
	_iic_host->SetSclCycleWhenGreater(std::chrono::microseconds{4});
	_iic_host->SetWaitingForAckTimeoutCycleCountWhenGreater(10);
}

std::string bsp::AT24C02_EEROM::Name() const
{
	return _name;
}

int32_t bsp::AT24C02_EEROM::Size() const
{
	return 256;
}

uint8_t bsp::AT24C02_EEROM::ReadByte(int32_t addr)
{
	_iic_host->SendStartingSignal();
	_iic_host->SendByte(0XA0 + ((addr / 256) << 1)); // 发送器件地址0XA0,写数据
	_iic_host->SendByte(addr % 256);                 // 发送低地址
	_iic_host->SendStartingSignal();
	_iic_host->SendByte(0XA1); // 进入接收模式
	uint8_t data = _iic_host->ReceiveByte(1);
	_iic_host->SendStoppingSignal();
	return data;
}

void bsp::AT24C02_EEROM::WriteByte(int32_t addr, uint8_t data)
{
	_iic_host->SendStartingSignal();
	_iic_host->SendByte(0XA0 + ((addr / 256) << 1)); // 发送器件地址0XA0,写数据
	_iic_host->SendByte(addr % 256);                 // 发送低地址
	_iic_host->SendByte(data);                       // 发送字节
	_iic_host->SendStoppingSignal();                 // 产生一个停止条件
	base::task::Delay(std::chrono::milliseconds{10});
}
