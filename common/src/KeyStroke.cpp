#include "KeyStroke.hpp"

KeyStroke::KeyStroke()
: APacket(APacket::PacketType::KEYSTROKES), _now(std::time(nullptr)), _data()
{

}

KeyStroke::KeyStroke(const std::string &data)
	: APacket(APacket::PacketType::KEYSTROKES), _now(std::time(nullptr)), _data(data)
{

}

KeyStroke::~KeyStroke()
{
    
}

std::vector<uint8_t> KeyStroke::to_bytes_body() const
{
    std::vector<uint8_t> ret;

	fill_bytes(ret, _now);
    fill_bytes(ret, static_cast<int>(_data.size()));
    for (auto c : _data)
        ret.push_back(c);
    return (ret);
}

void KeyStroke::to_readable_body(IReadable &parser) const
{
	parser.put("Time", _now);
	parser.put("Size", static_cast<int>(_data.size()));
	parser.put("Data", _data);
}

void KeyStroke::from_bytes_body(const std::vector<uint8_t> &bytes)
{
    std::size_t pos = 1;
    unsigned int size = 0;

	get_bytes(bytes, pos, _now);
    get_bytes(bytes, pos, size);
    for (;pos < bytes.size();pos++)
        _data += bytes[pos];
    if (pos - (sizeof(size) + sizeof(_type)) != size)
        throw std::invalid_argument("Error while parsing packet");
}

void KeyStroke::from_readable_body(IReadable &parser)
{
    int size;
    
	parser.get("Time", _now);
	parser.get("Size", size);
	parser.get("Data", _data);
    
    if (static_cast<unsigned int>(size) != _data.size())
        throw std::invalid_argument("Error while parsing packet");
}
