#ifndef _KEYSTROKE_HPP_
# define _KEYSTROKE_HPP_

# include "APacket.hpp"

class Keystroke: public APacket
{

public:
    Keystroke();
    Keystroke(const std::string &data);
    ~Keystroke();

    void print();

protected:
    virtual std::vector<char> to_bytes_body() const;
    virtual std::string to_readable_body() const;
    virtual void from_bytes_body(const std::vector<char> &bytes);
    virtual void from_readable_body(const std::string &data);
    
    
private:
    std::string _data;
};

#endif