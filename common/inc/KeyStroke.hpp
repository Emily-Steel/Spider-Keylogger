#ifndef _KEYSTROKE_HPP_
# define _KEYSTROKE_HPP_

# include "JSONParser.hpp"
# include "APacket.hpp"

class KeyStroke: public APacket
{

public:
    KeyStroke();
    KeyStroke(const std::string &data);
    ~KeyStroke();

    void print();

protected:
    virtual std::vector<char> to_bytes_body() const;
    virtual void to_readable_body(IReadable &parser) const;
    virtual void from_bytes_body(const std::vector<char> &bytes);
    virtual void from_readable_body(IReadable &parser);
    
    
private:
    std::string _data;
};

#endif