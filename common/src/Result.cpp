#include "Result.hpp"

Result::Result(PacketType type)
: APacket(type), _success(0)
{
    
}

Result::Result(PacketType type, char success)
: APacket(type), _success(success)
{
    
}

Result::~Result()
{
    
}

#include <iostream>

void Result::print()
{
    std::cout << "Type => " << (int)_type << std::endl;
    std::cout << (int)_success << std::endl;
}

std::vector<char> Result::to_bytes()
{
    std::vector<char> ret = to_byte_body();
    
    fill_bytes(ret, _success);
    return (ret);
}

std::string Result::to_readable()
{
    
}

void Result::from_bytes(const std::vector<char> &bytes)
{
    std::size_t pos = 1;
    
    if (bytes.empty() && bytes[0] != _type)
        throw PacketException("Error while parse packet");
    
    get_bytes(bytes, pos, _success);
}

void Result::from_readable(const std::string &data)
{
    
}
