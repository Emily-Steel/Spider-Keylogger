#include "APacket.hpp"

APacket::APacket(PacketType type)
: _type(type)
{
    
}

APacket::~APacket()
{
    
}

std::vector<char> APacket::to_bytes() const
{
    std::vector<char> ret;
    std::vector<char> tmp = to_bytes_body();

    ret.push_back(_type);
    ret.insert(ret.end(), tmp.begin(), tmp.end());
    return (ret);
}

std::string APacket::to_readable() const
{
    return ("");
}

void APacket::from_bytes(const std::vector<char> &bytes)
{
    if (bytes.empty() && bytes[0] != _type)
        throw std::invalid_argument("Error while parse packet");
    from_bytes_body(bytes);
}

void APacket::from_readable(const std::string &data)
{
    std::size_t pos;
    if ((pos = data.find(JSONPAIR)) != std::string::npos)
    {
        pos += JSONPAIRSIZE;
        std::stringstream ss(data.substr(pos));
        ss >> _type;
    }
}
