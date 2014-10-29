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
    std::string ret("");
    std::stringstream ss("");
    
    ss << static_cast<int>(_type);
    _parser->clear();
    _parser->put("Type", ss.str());
    to_readable_body();
    _parser->write(ret);
    return (ret);
}

void APacket::from_bytes(const std::vector<char> &bytes)
{
    if (bytes.empty() && bytes[0] != _type)
        throw std::invalid_argument("Error while parse packet");
    from_bytes_body(bytes);
}

void APacket::from_readable(const std::string &data)
{
    std::string tmp;
    int type;
    std::stringstream ss("");
    
    _parser->clear();
    _parser->read(data);
    _parser->get("Type", tmp);
    ss.str(tmp);
    ss >> type;
    if (type != _type && !tmp.empty())
        throw std::invalid_argument("Error while parsing packet");
    from_readable_body();
}
