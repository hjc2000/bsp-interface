#include "MutexEthernetPort.h"

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

bsp::Ethernet_DuplexMode bsp::MutexEthernetPort::DuplexMode()
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
	base::LockGuard l{*_lock};
	_port->Send(spans);
}

base::IEnumerable<base::ReadOnlySpan> const &bsp::MutexEthernetPort::Receive()
{
	base::LockGuard l{*_lock};
	return _port->Receive();
}

bsp::MutexEthernetPort::MutexEthernetPort(bsp::IEthernetPort *port)
{
	base::LockGuard l{*_lock};
	_port = port;
}
