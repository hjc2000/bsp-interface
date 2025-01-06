#include "MutexEthernetPort.h"

bsp::MutexEthernetPort::MutexEthernetPort(bsp::IEthernetPort *port)
{
	_port = port;
}

std::string bsp::MutexEthernetPort::Name() const
{
	base::LockGuard l{*_lock};
	return _port->Name();
}

void bsp::MutexEthernetPort::Open(base::Mac const &mac)
{
	base::LockGuard l{*_lock};
	_port->Open(mac);
}

uint32_t bsp::MutexEthernetPort::ReadPHYRegister(uint32_t register_index)
{
	base::LockGuard l{*_lock};
	return _port->ReadPHYRegister(register_index);
}

void bsp::MutexEthernetPort::WritePHYRegister(uint32_t register_index, uint32_t value)
{
	base::LockGuard l{*_lock};
	_port->WritePHYRegister(register_index, value);
}

void bsp::MutexEthernetPort::Restart()
{
	base::LockGuard l{*_lock};
	_port->Restart();
}

void bsp::MutexEthernetPort::ResetPHY()
{
	base::LockGuard l{*_lock};
	_port->ResetPHY();
}

bsp::EthernetDuplexMode bsp::MutexEthernetPort::DuplexMode()
{
	base::LockGuard l{*_lock};
	return _port->DuplexMode();
}

base::Bps bsp::MutexEthernetPort::Speed()
{
	base::LockGuard l{*_lock};
	return _port->Speed();
}

void bsp::MutexEthernetPort::Send(base::IEnumerable<base::ReadOnlySpan> const &spans)
{
	base::LockGuard l{*_sending_lock};
	_port->Send(spans);
}

void bsp::MutexEthernetPort::Send(base::ReadOnlySpan const &span)
{
	base::LockGuard l{*_sending_lock};
	_port->Send(span);
}

base::IEvent<base::ReadOnlySpan> &bsp::MutexEthernetPort::ReceivintEhternetFrameEvent()
{
	base::LockGuard l{*_receiving_lock};
	return _port->ReceivintEhternetFrameEvent();
}

void bsp::MutexEthernetPort::SoftwareResetPHY()
{
	base::LockGuard l{*_lock};
	_port->SoftwareResetPHY();
}

bool bsp::MutexEthernetPort::SupportAutoNegotiation()
{
	base::LockGuard l{*_lock};
	return _port->SupportAutoNegotiation();
}

void bsp::MutexEthernetPort::EnableAutoNegotiation()
{
	base::LockGuard l{*_lock};
	_port->EnableAutoNegotiation();
}

bool bsp::MutexEthernetPort::AutoNegotiationCompleted()
{
	base::LockGuard l{*_lock};
	return _port->AutoNegotiationCompleted();
}

void bsp::MutexEthernetPort::EnablePowerDownMode()
{
	base::LockGuard l{*_lock};
	_port->EnablePowerDownMode();
}

void bsp::MutexEthernetPort::DisablePowerDownMode()
{
	base::LockGuard l{*_lock};
	_port->DisablePowerDownMode();
}

void bsp::MutexEthernetPort::EnableLoopbackMode()
{
	base::LockGuard l{*_lock};
	_port->EnableLoopbackMode();
}

void bsp::MutexEthernetPort::DisableLoopbackMode()
{
	base::LockGuard l{*_lock};
	_port->DisableLoopbackMode();
}

bool bsp::MutexEthernetPort::IsLinked()
{
	base::LockGuard l{*_lock};
	return _port->IsLinked();
}
