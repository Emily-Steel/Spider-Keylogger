#include <iostream>

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

void Result::print()
{
    std::cout << "Type => " << (int)_type << std::endl;
    std::cout << (int)_success << std::endl;
}

std::vector<uint8_t> Result::to_bytes_body() const
{
    std::vector<uint8_t> ret;
    
    fill_bytes(ret, _success);
    return (ret);
}

void Result::to_readable_body(IReadable &parser) const
{
    parser.put("Success", _success);
}

void Result::from_bytes_body(const std::vector<uint8_t> &bytes)
{
    std::size_t pos = 1;

    get_bytes(bytes, pos, _success);
}

void Result::from_readable_body(IReadable &parser)
{
    parser.get("Success", _success);
}
