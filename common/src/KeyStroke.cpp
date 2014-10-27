#include "KeyStroke.hpp"

Keystroke::Keystroke()
: APacket(KEYSTROKES), _data()
{

}

Keystroke::Keystroke(const std::string &data)
: APacket(KEYSTROKES), _data(data)
{
    
}

Keystroke::~Keystroke()
{
    
}

#include <iostream>

void Keystroke::print()
{
    std::cout << (int)_type << std::endl;
    std::cout << _data << std::endl;
}

std::vector<char> Keystroke::to_bytes() const
{
    std::vector<char> ret = to_byte_body();

    fill_bytes(ret, static_cast<int>(_data.size()));
    for (auto c : _data)
        ret.push_back(c);
    return (ret);
}

std::string Keystroke::to_readable() const
{
    
}

void Keystroke::from_bytes(const std::vector<char> &bytes)
{
    std::size_t pos = 1;
    unsigned int size = 0;

    if (bytes.empty() && bytes[0] != _type)
        throw PacketException("Error while parse packet");

    get_bytes(bytes, pos, size);
    
    for (;pos < bytes.size();pos++)
        _data += bytes[pos];
    if (pos - (sizeof(int) + 1) != size)
        throw PacketException("Error while parse packet");
}

void Keystroke::from_readable(const std::string &data)
{
    
}
