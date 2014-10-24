#include "ScreenShot.hpp"

ScreenShot::ScreenShot()
: APacket(SCREENSHOT), _success(0), _data("")
{
    
}

ScreenShot::ScreenShot(char success, const std::string &data)
: APacket(SCREENSHOT), _success(success), _data(data)
{
    
}

ScreenShot::~ScreenShot()
{
    
}

#include <iostream>

void ScreenShot::print()
{
    std::cout << (int)_type << std::endl;
    std::cout << (int)_success << std::endl;
    std::cout << _data << std::endl;
}

std::vector<char> ScreenShot::to_bytes()
{
    std::vector<char> ret = to_byte_body();
    
    fill_bytes(ret, _success);
    if (_success == DONE)
    {
        fill_bytes(ret, static_cast<int>(_data.size()));
        for (auto c : _data)
            ret.push_back(c);
    }
    return (ret);
}

std::string ScreenShot::to_readable()
{
    
}

void ScreenShot::from_bytes(const std::vector<char> &bytes)
{
    std::size_t pos = 1;
    int size = 0;
    
    if (bytes.empty() && bytes[0] != _type)
        throw PacketException("Error while parse packet");
    
    get_bytes(bytes, pos, _success);
    if (_success == DONE)
    {
        get_bytes(bytes, pos, size);
        for (;pos < bytes.size();pos++)
            _data += bytes[pos];
        if (pos - (sizeof(int) + sizeof(char) + 1) != size)
            throw PacketException("Error while parse packet");
    }
}

void ScreenShot::from_readable(const std::string &data)
{
    
}
