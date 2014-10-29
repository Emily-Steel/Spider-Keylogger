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

std::vector<char> MouseClick::to_bytes_body() const
{
    std::vector<char> ret;
    
    fill_bytes(ret, _button);
    fill_bytes(ret, _posX);
    fill_bytes(ret, _posY);
    return (ret);
}

void MouseClick::to_readable_body() const
{

}

void MouseClick::from_bytes_body(const std::vector<char> &bytes)
{
    std::size_t pos = 1;
    
    get_bytes(bytes, pos, _button);
    get_bytes(bytes, pos, _posX);
    get_bytes(bytes, pos, _posY);
    
}

void MouseClick::from_readable_body()
{
    
}
