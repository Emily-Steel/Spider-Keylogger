#include "SocketFactory.hpp"

SocketFactory::SocketFactory()
{
    
}

SocketFactory::~SocketFactory()
{
    
}

ISocket *SocketFactory::createSocket()
{
    return (new BoostSocket());
}