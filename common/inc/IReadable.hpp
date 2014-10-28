#ifndef _AREADABLE_HPP_
# define _AREADABLE_HPP_

# include <string>

class IReadable
{
public:
    virtual ~IReadable() {};

    virtual void put(const std::string &key, const std::string &value) = 0;
    virtual void get(const std::string &key, std::string &value) = 0;
    
    virtual void getReadable(const std::string &) = 0;
    virtual void setReadable(std::string &) = 0;
};

#endif