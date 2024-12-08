#include "MutexIicHost.h"

bsp::MutexIicHost::MutexIicHost(bsp::IIicHost *host)
{
    _host = host;
}

std::string bsp::MutexIicHost::Name() const
{
    base::LockGuard l{*_lock};
    return _host->Name();
}

void bsp::MutexIicHost::SendStartingSignal()
{
    base::LockGuard l{*_lock};
    _host->SendStartingSignal();
}

void bsp::MutexIicHost::SendStoppingSignal()
{
    base::LockGuard l{*_lock};
    _host->SendStoppingSignal();
}

void bsp::MutexIicHost::SendByte(uint8_t value)
{
    base::LockGuard l{*_lock};
    _host->SendByte(value);
}

uint8_t bsp::MutexIicHost::ReceiveByte(bool send_nack)
{
    base::LockGuard l{*_lock};
    return _host->ReceiveByte(send_nack);
}

std::chrono::microseconds bsp::MutexIicHost::SclCycle() const
{
    base::LockGuard l{*_lock};
    return _host->SclCycle();
}

void bsp::MutexIicHost::SetSclCycle(std::chrono::microseconds value)
{
    base::LockGuard l{*_lock};
    _host->SetSclCycle(value);
}

int bsp::MutexIicHost::WaitingForAckTimeoutCycleCount() const
{
    base::LockGuard l{*_lock};
    return _host->WaitingForAckTimeoutCycleCount();
}

void bsp::MutexIicHost::SetWaitingForAckTimeoutCycleCount(int value)
{
    base::LockGuard l{*_lock};
    _host->SetWaitingForAckTimeoutCycleCount(value);
}
