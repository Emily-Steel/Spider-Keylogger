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

std::vector<char> Result::to_bytes_body() const
{
    std::vector<char> ret;
    
    fill_bytes(ret, _success);
    return (ret);
}

std::string Result::to_readable_body() const
{
    
}

void Result::from_bytes_body(const std::vector<char> &bytes)
{
    std::size_t pos = 1;

    get_bytes(bytes, pos, _success);
}

void Result::from_readable_body(const std::string &data)
{
    
}
