#include "BoostSocket.hpp"
BoostSocket::BoostSocket()
{
    
}

BoostSocket::~BoostSocket()
{
    
}

bool BoostSocket::connect (std::string address, int port)
{
    
}

ISocket &BoostSocket::operator<<(const APacket &packet)
{
    
}

ISocket &BoostSocket::operator>>(APacket &packet)
{
    
}

bool BoostSocket::write(void *data, std::size_t size)
{
    
}

bool BoostSocket::read(const std::string buffer, std::size_t size)
{
    
}

void BoostSocket::bind(int port)
{
    
}

void BoostSocket::listen(std::size_t backlog)
{
    
}

ISocket *BoostSocket::accept()
{
    
}
