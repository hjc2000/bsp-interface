#include "MutexIicHost.h"

bsp::MutexIicHost::MutexIicHost(bsp::IIicHost *host)
{
	_host = host;
}

std::string bsp::MutexIicHost::Name() const
{
	base::task::MutexGuard g{_lock};
	return _host->Name();
}

void bsp::MutexIicHost::SendStartingSignal()
{
	base::task::MutexGuard g{_lock};
	_host->SendStartingSignal();
}

void bsp::MutexIicHost::SendStoppingSignal()
{
	base::task::MutexGuard g{_lock};
	_host->SendStoppingSignal();
}

void bsp::MutexIicHost::SendByte(uint8_t value)
{
	base::task::MutexGuard g{_lock};
	_host->SendByte(value);
}

uint8_t bsp::MutexIicHost::ReceiveByte(bool send_nack)
{
	base::task::MutexGuard g{_lock};
	return _host->ReceiveByte(send_nack);
}

std::chrono::microseconds bsp::MutexIicHost::SclCycle() const
{
	base::task::MutexGuard g{_lock};
	return _host->SclCycle();
}

void bsp::MutexIicHost::SetSclCycle(std::chrono::microseconds value)
{
	base::task::MutexGuard g{_lock};
	_host->SetSclCycle(value);
}

int bsp::MutexIicHost::WaitingForAckTimeoutCycleCount() const
{
	base::task::MutexGuard g{_lock};
	return _host->WaitingForAckTimeoutCycleCount();
}

void bsp::MutexIicHost::SetWaitingForAckTimeoutCycleCount(int value)
{
	base::task::MutexGuard g{_lock};
	_host->SetWaitingForAckTimeoutCycleCount(value);
}

void bsp::MutexIicHost::SetSclCycleWhenGreater(std::chrono::microseconds value)
{
	base::task::MutexGuard g{_lock};
	_host->SetSclCycleWhenGreater(value);
}

void bsp::MutexIicHost::SetWaitingForAckTimeoutCycleCountWhenGreater(int value)
{
	base::task::MutexGuard g{_lock};
	_host->SetWaitingForAckTimeoutCycleCountWhenGreater(value);
}
