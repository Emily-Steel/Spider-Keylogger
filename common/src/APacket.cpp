#include "APacket.hpp"

APacket::APacket(PacketType type)
: _type(static_cast<uint8_t>(type)), _now(time(NULL))
{
}

APacket::~APacket()
{
    
}

std::vector<uint8_t> APacket::to_bytes() const
{
    std::vector<uint8_t> ret;
    std::vector<uint8_t> tmp = to_bytes_body();

    ret.push_back(_type);
	//fill_bytes(ret, _now);
    ret.insert(ret.end(), tmp.begin(), tmp.end());
    return (ret);
}

void APacket::to_readable(IReadable &parser) const
{
    std::string ret;
    
    parser.clear();
    parser.put("Type", static_cast<int>(_type));
    parser.put("Time", _now);
    to_readable_body(parser);
}

void APacket::from_bytes(const std::vector<uint8_t> &bytes)
{
    if (bytes.empty() && bytes[0] != _type)
        throw std::invalid_argument("Error while parsing packet");
    from_bytes_body(bytes);
}

void APacket::from_readable(std::string &data, IReadable &parser)
{
    int type = -1;
    
    parser.clear();
    parser.read(data);
    parser.get("Type", type);
    parser.get("Time", _now);
    if (type != _type)
        throw std::invalid_argument("Error while parsing packet");
    from_readable_body(parser);
}
