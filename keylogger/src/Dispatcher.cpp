#include "FileLog.hpp"
#include "Dispatcher.hpp"

Dispatcher::Dispatcher()
: _log(new FileLog())
{
    
}

Dispatcher::~Dispatcher()
{
    
}

void                    Dispatcher::dispatch(const APacket &packet)
{
    if (_net.isConnected())
        _net << packet;
    else
        _log->insert(packet, "Save");
}

void                    Dispatcher::handlePacket(APacket &packet)
{
    
}

std::vector<APacket *>  Dispatcher::pollNetwork()
{
	std::vector<APacket *> ret;

	return (ret);
}
