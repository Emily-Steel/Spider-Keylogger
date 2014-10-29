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

std::vector<char> ScreenShot::to_bytes_body() const
{
    std::vector<char> ret;
    
    fill_bytes(ret, _success);
    if (_success == DONE)
    {
        fill_bytes(ret, static_cast<int>(_data.size()));
        for (auto c : _data)
            ret.push_back(c);
    }
    return (ret);
}

void ScreenShot::to_readable_body(IReadable &parser) const
{
    parser.put("Success", _success);
    if (_success == DONE)
    {
        parser.put("Size", static_cast<int>(_data.size()));
        parser.put("Data", _data);
    }
}

void ScreenShot::from_bytes_body(const std::vector<char> &bytes)
{
    std::size_t pos = 1;
    unsigned int size = 0;
    
    get_bytes(bytes, pos, _success);
    if (_success == DONE)
    {
        get_bytes(bytes, pos, size);
        for (;pos < bytes.size();pos++)
            _data += bytes[pos];
        if (pos - (sizeof(size) + sizeof(_type) + 1) != size)
            throw std::invalid_argument("Error while parsing packet");
    }
}

void ScreenShot::from_readable_body(IReadable &parser)
{
    int size;

    parser.get("Success", _success);
    if (_success == DONE)
    {
        parser.get("Size", size);
        parser.get("Data", _data);
        
        if (size != _data.size())
            throw std::invalid_argument("Error while parsing packet");
    }   
}
