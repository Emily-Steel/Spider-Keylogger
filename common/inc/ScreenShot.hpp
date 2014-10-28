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
    
    void print();
    
protected:
    virtual std::vector<char> to_bytes_body() const;
    virtual std::string to_readable_body() const;
    virtual void from_bytes_body(const std::vector<char> &bytes);
    virtual void from_readable_body(const std::string &data);

    
private:
    char        _success;
    std::string _data;
};

#endif