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

std::vector<char> Keystroke::to_bytes_body() const
{
    std::vector<char> ret;

    fill_bytes(ret, static_cast<int>(_data.size()));
    for (auto c : _data)
        ret.push_back(c);
    return (ret);
}

void Keystroke::to_readable_body(IReadable &parser) const
{
    parser.put("Size", static_cast<int>(_data.size()));
    parser.put("Data", _data);
}

void Keystroke::from_bytes_body(const std::vector<char> &bytes)
{
    std::size_t pos = 1;
    unsigned int size = 0;

    get_bytes(bytes, pos, size);
    for (;pos < bytes.size();pos++)
        _data += bytes[pos];
    if (pos - (sizeof(size) + sizeof(_type)) != size)
        throw std::invalid_argument("Error while parsing packet");
}

void Keystroke::from_readable_body(IReadable &parser)
{
    int size;
    
    parser.get("Size", size);
    parser.get("Data", _data);
    
    if (static_cast<unsigned int>(size) != _data.size())
        throw std::invalid_argument("Error while parsing packet");
}
