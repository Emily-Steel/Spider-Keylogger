#include "KeyStroke.hpp"

Keystroke::Keystroke()
: APacket(KEYSTROKES), _data()
{
    _parser = new JSONParser;
}

Keystroke::Keystroke(const std::string &data)
: APacket(KEYSTROKES), _data(data)
{
    _parser = new JSONParser;    
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

void Keystroke::to_readable_body() const
{
    std::stringstream ss("");

    ss << _data.size();
    _parser->put("Size", ss.str());
    _parser->put("Data", _data);
}

void Keystroke::from_bytes_body(const std::vector<char> &bytes)
{
    std::size_t pos = 1;
    unsigned int size = 0;

    get_bytes(bytes, pos, size);
    for (;pos < bytes.size();pos++)
        _data += bytes[pos];
    if (pos - (sizeof(int) + 1) != size)
        throw std::invalid_argument("Error while parsing packet");
}

void Keystroke::from_readable_body()
{
    std::size_t size;
    std::string tmp;
    std::stringstream ss("");
    
    _parser->get("Size", tmp);
    _parser->get("Data", _data);
    
    ss << tmp;
    ss >> size;
    
    if (size != _data.size())
        throw std::invalid_argument("Error while parsing packet");
}
