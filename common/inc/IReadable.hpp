#ifndef _AREADABLE_HPP_
# define _AREADABLE_HPP_

# include <string>

class IReadable
{
public:
    virtual ~IReadable() {};

    virtual void put(const std::string &key, const std::string &value) = 0;
    virtual void put(const std::string &key, const int &value) = 0;
    virtual void put(const std::string &key, const short &value) = 0;
    virtual void put(const std::string &key, const char &value) = 0;

    
    virtual void get(const std::string &key, std::string &value) = 0;
    virtual void get(const std::string &key, int &value) = 0;
    virtual void get(const std::string &key, short &value) = 0;
    virtual void get(const std::string &key, char &value) = 0;
    
    virtual void read(std::string &) = 0;
    virtual void write(std::string &) = 0;
    
    virtual void clear() = 0;
};

#endif