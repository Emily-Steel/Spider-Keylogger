#include "ScreenShot.hpp"

#include <iostream>

ScreenShot::ScreenShot()
: APacket(APacket::PacketType::SCREENSHOT), _success(false), _data("")
{
    
}

ScreenShot::ScreenShot(bool success, const std::string &data)
: APacket(APacket::PacketType::SCREENSHOT), _success(success), _data(data)
{
    
}

ScreenShot::~ScreenShot()
{
    
}

void ScreenShot::print()
{
    std::cout << static_cast<uint8_t>(_type) << std::endl;
    std::cout << _success << std::endl;
    std::cout << _data << std::endl;
}

std::vector<uint8_t> ScreenShot::to_bytes_body() const
{
    std::vector<uint8_t> ret;
    
    fill_bytes(ret, _success);
    if (_success)
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
    if (_success)
    {
        parser.put("Size", static_cast<int>(_data.size()));
        parser.put("Data", _data);
    }
}

void ScreenShot::from_bytes_body(const std::vector<uint8_t> &bytes)
{
    std::size_t pos = 1;
    unsigned int size = 0;
    
    get_bytes(bytes, pos, _success);
    if (_success)
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
    char succ;

    parser.get("Success", succ);
    _success = succ;
    if (_success)
    {
        parser.get("Size", size);
        parser.get("Data", _data);
        
        if (static_cast<unsigned int>(size) != _data.size())
            throw std::invalid_argument("Error while parsing packet");
    }   
}
