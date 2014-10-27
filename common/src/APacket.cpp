#include <iostream>
#include <sstream>
#include "APacket.hpp"

APacket::APacket(PacketType type)
: _type(type)
{
    
}

APacket::~APacket()
{
    
}

std::vector<char> APacket::to_byte_body() const
{
    std::vector<char> ret;

    ret.push_back(_type);
    return (ret);
}

std::string APacket::to_readable_body() const
{
    std::stringstream ss(JSONPAIR);
    
    ss << _type;
    return (ss.str());
}

void APacket::from_byte_body(const std::vector<char> &bytes)
{
    if (bytes.size() > 1)
        _type = bytes[0];
}

void APacket::from_readable_body(const std::string &data)
{
    std::size_t pos;
    if ((pos = data.find(JSONPAIR)) != std::string::npos)
    {
        pos += JSONPAIRSIZE;
        std::stringstream ss(data.substr(pos));
        ss >> _type;
    }
}
