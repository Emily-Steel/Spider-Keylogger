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
    virtual void get(const std::string &key, std::string &value);
    
    virtual void read(const std::string &);
    virtual void write(std::string &);
    
    virtual void clear();
    
private:
    boost::property_tree::ptree _json;
};

#endif
