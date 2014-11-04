#include "JSONParser.hpp"


JSONParser::JSONParser()
: IReadable()
{
    
}

JSONParser::~JSONParser()
{
    
}

void JSONParser::put(const std::string &key, const std::string &value)
{
    _json.put(key, value);
}

void JSONParser::put(const std::string &key, const int &value)
{
    _json.put(key, value);
}

void JSONParser::put(const std::string &key, const short &value)
{
    _json.put(key, value);
}

void JSONParser::put(const std::string &key, const char &value)
{
    _json.put(key, value);
}

void JSONParser::get(const std::string &key, std::string &value)
{
    value = _json.get<std::string>(key);
}

void JSONParser::get(const std::string &key, int &value)
{
    value = _json.get<int>(key);
}

void JSONParser::get(const std::string &key, short &value)
{
    value = _json.get<short>(key);
}

void JSONParser::get(const std::string &key, char &value)
{
    value = _json.get<char>(key);
}

void JSONParser::read(std::string &str)
{
    std::stringstream ss(std::string(str.substr(0, str.find("}")) + "}"));

    str = str.substr(str.find("}") + 1);
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