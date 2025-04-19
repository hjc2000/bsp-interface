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

void bsp::MutexEthernetPort::Send(std::vector<base::ReadOnlySpan> const &spans)
{
	base::LockGuard l{*_sending_lock};
	_port->Send(spans);
}

void bsp::MutexEthernetPort::Send(base::ReadOnlySpan const &span)
{
	base::LockGuard l{*_sending_lock};
	_port->Send(span);
}

base::IEvent<base::ReadOnlySpan> &bsp::MutexEthernetPort::ReceivingEhternetFrameEvent()
{
	base::LockGuard l{*_sending_lock};
	return _port->ReceivingEhternetFrameEvent();
}

base::IEvent<> &bsp::MutexEthernetPort::ConnectionEvent()
{
	base::LockGuard l{*_sending_lock};
	return _port->ConnectionEvent();
}

base::IEvent<> &bsp::MutexEthernetPort::DisconnectionEvent()
{
	base::LockGuard l{*_sending_lock};
	return _port->DisconnectionEvent();
}
