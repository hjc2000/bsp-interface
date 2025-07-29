#include "AT24C02_EEROM.h"
#include "base/task/delay.h"

bsp::AT24C02_EEROM::AT24C02_EEROM(std::string const &name,
								  std::shared_ptr<base::iic::IicHost> const &host)
{
	/* IIC 设备类不能自己去调用 IIicHost 的打开方法或初始化方法，因为一个 IIicHost
	 * 对象可能给多个 IIC 设备类对象共用，如果每个 IIC 设备类对象都要 Open 一次，那就
	 * 乱套了。而且 IIC 接口各种各样，可能有很多 Open 的重载版本和初始化方式。
	 *
	 * 综上，Open 的工作应该在 IIC 设备类外部完成。
	 */

	_name = name;
	_iic_host = host;
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
	base::iic::IicHostOperator op{*_iic_host};

	op.Initialize(base::unit::Nanosecond{std::chrono::microseconds{4}},
				  base::unit::Nanosecond{std::chrono::microseconds{4} * 20});

	op.SendStartingSignal();
	op.SendByte(0XA0 + ((addr / 256) << 1)); // 发送器件地址0XA0,写数据
	op.SendByte(addr % 256);                 // 发送低地址
	op.SendStartingSignal();
	op.SendByte(0XA1); // 进入接收模式
	uint8_t data = op.ReceiveByte(1);
	op.SendStoppingSignal();
	return data;
}

void bsp::AT24C02_EEROM::WriteByte(int32_t addr, uint8_t data)
{
	base::iic::IicHostOperator op{*_iic_host};

	op.Initialize(base::unit::Nanosecond{std::chrono::microseconds{4}},
				  base::unit::Nanosecond{std::chrono::microseconds{4} * 20});

	op.SendStartingSignal();
	op.SendByte(0XA0 + ((addr / 256) << 1)); // 发送器件地址0XA0,写数据
	op.SendByte(addr % 256);                 // 发送低地址
	op.SendByte(data);                       // 发送字节
	op.SendStoppingSignal();                 // 产生一个停止条件
	base::task::Delay(std::chrono::milliseconds{10});
}
