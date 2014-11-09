#ifndef Project_JSONParser_h
# define Project_JSONParser_h

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "IReadable.hpp"

class JSONParser: public IReadable
{
public:
    JSONParser();
    ~JSONParser();
    
    virtual void put(const std::string &key, const std::string &value);
    virtual void put(const std::string &key, const unsigned long &value);
    virtual void put(const std::string &key, const int &value);
    virtual void put(const std::string &key, const short &value);
    virtual void put(const std::string &key, const char &value);

    virtual void get(const std::string &key, std::string &value);
    virtual void get(const std::string &key, unsigned long &value);
    virtual void get(const std::string &key, int &value);
    virtual void get(const std::string &key, short &value);
    virtual void get(const std::string &key, char &value);

    virtual void read(std::string &);
    virtual void write(std::string &);
    
    virtual void clear();
    
private:
    boost::property_tree::ptree _json;
};

#endif
