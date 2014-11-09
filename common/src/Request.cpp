#include "Request.hpp"

Request::Request(PacketType type)
: APacket(type)
{
    
}

Request::~Request()
{
    
}

std::vector<uint8_t> Request::to_bytes_body() const
{
    return (std::vector<uint8_t>());
}

void Request::to_readable_body(IReadable &) const
{

}

void Request::from_bytes_body(const std::vector<uint8_t> &)
{
    
}

void Request::from_readable_body(IReadable &)
{
    
}
