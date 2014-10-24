#include "Request.hpp"

Request::Request(PacketType type)
: APacket(type)
{
    
}

Request::~Request()
{
    
}

#include <iostream>

void Request::print()
{
    std::cout << (int)_type << std::endl;
}

std::vector<char> Request::to_bytes()
{
    return (to_byte_body());
}

std::string Request::to_readable()
{
    
}

void Request::from_bytes(const std::vector<char> &bytes)
{
    std::size_t pos = 1;
    
    if (bytes.empty() && bytes[0] != _type)
        throw PacketException("Error while parse packet");
}

void Request::from_readable(const std::string &data)
{
    
}
