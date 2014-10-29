#include "JSONParser.hpp"


JSONParser::JSONParser()
{
    
}

JSONParser::~JSONParser()
{
    
}

void JSONParser::put(const std::string &key, const std::string &value)
{
    _json.put(key, value);
}

void JSONParser::get(const std::string &key, std::string &value)
{
    value = _json.get<std::string>(key);
}

void JSONParser::read(const std::string &str)
{
    std::stringstream ss(str);

    boost::property_tree::read_json(ss, _json);
}

void JSONParser::write(std::string &str)
{
    std::stringstream ss("");
    
    boost::property_tree::write_json(ss, _json);
    str = ss.str();
}

void JSONParser::clear()
{
    _json.clear();
}