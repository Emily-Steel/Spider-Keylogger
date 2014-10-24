#ifndef _SCREENSHOT_HPP_
# define _SCREENSHOT_HPP_

# include <string>
# include "APacket.hpp"

class ScreenShot: public APacket
{
    
public:
    ScreenShot();
    ScreenShot(char success, const std::string &data = "");
    ~ScreenShot();
    
    virtual std::vector<char> to_bytes();
    virtual std::string to_readable();
    virtual void from_bytes(const std::vector<char> &bytes);
    virtual void from_readable(const std::string &data);
    
    void print();
    
private:
    char        _success;
    std::string _data;
};

#endif