#include "GpioSoftwareIicHost.h"
#include "base/embedded/gpio/gpio_parameter.h"

bsp::GpioSoftwareIicHost::GpioSoftwareIicHost(std::string name,
											  std::shared_ptr<base::iic::ISoftwareIicHostPinDriver> const &pin_driver)
{
	_name = name;
	_pin_driver = pin_driver;
}

std::string bsp::GpioSoftwareIicHost::Name() const
{
	return _name;
}

void bsp::GpioSoftwareIicHost::WriteSCL(bool value)
{
	_pin_driver->WriteSCL(value);
}

void bsp::GpioSoftwareIicHost::ChangeSDADirection(base::gpio::Direction value)
{
	_pin_driver->ChangeSDADirection(value);
}

void bsp::GpioSoftwareIicHost::WriteSDA(bool value)
{
	_pin_driver->WriteSDA(value);
}

bool bsp::GpioSoftwareIicHost::ReadSDA() const
{
	return _pin_driver->ReadSDA();
}

std::chrono::microseconds bsp::GpioSoftwareIicHost::SclCycle() const
{
	return _scl_cycle;
}

void bsp::GpioSoftwareIicHost::SetSclCycle(std::chrono::microseconds value)
{
	_scl_cycle = value;
}

int bsp::GpioSoftwareIicHost::WaitingForAckTimeoutCycleCount() const
{
	return _waiting_for_ack_timeout_cycle;
}

void bsp::GpioSoftwareIicHost::SetWaitingForAckTimeoutCycleCount(int value)
{
	_waiting_for_ack_timeout_cycle = value;
}
