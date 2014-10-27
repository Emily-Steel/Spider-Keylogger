#include "MouseClick.hpp"

MouseClick::MouseClick()
: APacket(MOUSECLICK), _button(0), _posX(0), _posY(0)
{
    
}

MouseClick::MouseClick(unsigned char button, unsigned short posX, unsigned short posY)
: APacket(MOUSECLICK), _button(button), _posX(posX), _posY(posY)
{
    
}

MouseClick::~MouseClick()
{
    
}

#include <iostream>

void MouseClick::print()
{
    std::cout << (int)_type << std::endl;
    std::cout << (int)_button << std::endl;
    std::cout << _posX << std::endl;
    std::cout << _posY << std::endl;
}

std::vector<char> MouseClick::to_bytes() const
{
    std::vector<char> ret = to_byte_body();
    
    fill_bytes(ret, _button);
    fill_bytes(ret, _posX);
    fill_bytes(ret, _posY);
    return (ret);
}

std::string MouseClick::to_readable() const
{
    
}

void MouseClick::from_bytes(const std::vector<char> &bytes)
{
    std::size_t pos = 1;
    
    if (bytes.empty() && bytes[0] != _type)
        throw PacketException("Error while parse packet");
    
    get_bytes(bytes, pos, _button);
    get_bytes(bytes, pos, _posX);
    get_bytes(bytes, pos, _posY);
    
}

void MouseClick::from_readable(const std::string &data)
{
    
}
