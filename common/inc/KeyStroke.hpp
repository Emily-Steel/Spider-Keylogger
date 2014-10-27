#ifndef _KEYSTROKE_HPP_
# define _KEYSTROKE_HPP_

# include "APacket.hpp"

class Keystroke: public APacket
{

public:
    Keystroke();
    Keystroke(const std::string &data);
    ~Keystroke();
    
    virtual std::vector<char> to_bytes() const;
    virtual std::string to_readable() const;
    virtual void from_bytes(const std::vector<char> &bytes);
    virtual void from_readable(const std::string &data);
    
    void print();
    
private:
    std::string _data;
};

#endif