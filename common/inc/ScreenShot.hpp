#ifndef _SCREENSHOT_HPP_
# define _SCREENSHOT_HPP_

# include <string>
# include "APacket.hpp"

class ScreenShot: public APacket
{
    
public:
    ScreenShot();
    ScreenShot(bool success, const std::string &data = "");
    ~ScreenShot();
    
protected:
    virtual std::vector<uint8_t> to_bytes_body() const;
    virtual void to_readable_body(IReadable &parser) const;
    virtual void from_bytes_body(const std::vector<uint8_t> &bytes);
    virtual void from_readable_body(IReadable &parser);

    
private:
    bool        _success;
    std::string _data;
};

#endif