#ifndef _MOUSECLICK_HPP_
# define _MOUSECLICK_HPP_

# include "APacket.hpp"

class MouseClick: public APacket
{
    
public:
    MouseClick();
    MouseClick(unsigned char button, unsigned short posX, unsigned short posY);
    ~MouseClick();
    
    virtual std::vector<char> to_bytes() const;
    virtual std::string to_readable() const;
    virtual void from_bytes(const std::vector<char> &bytes);
    virtual void from_readable(const std::string &data);
    
    void print();
    
private:
    unsigned char   _button;
    unsigned short  _posX;
    unsigned short  _posY;
};

#endif