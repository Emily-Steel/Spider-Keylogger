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
    try
    {
        value = _json.get<std::string>(key);
    }
    catch(boost::property_tree::ptree_bad_data e)
    {
        throw std::invalid_argument("Cannot find " + key);
    }
}

void JSONParser::get(const std::string &key, int &value)
{
    try
    {
        value = _json.get<int>(key);
    }
    catch(boost::property_tree::ptree_bad_data e)
    {
        throw std::invalid_argument("Cannot find " + key);
    }
}

void JSONParser::get(const std::string &key, short &value)
{
    try
    {
        value = _json.get<short>(key);
    }
    catch(boost::property_tree::ptree_bad_data e)
    {
        throw std::invalid_argument("Cannot find " + key);
    }
}

void JSONParser::get(const std::string &key, char &value)
{
    try
    {
        value = _json.get<char>(key);
    }
    catch(boost::property_tree::ptree_bad_data e)
    {
        throw std::invalid_argument("Cannot find " + key);
    }
}

void JSONParser::read(std::string &str)
{
    try
    {
        std::stringstream ss(std::string(str.substr(0, str.find("}")) + "}"));

        str = str.substr(str.find("}") + 1);
        boost::property_tree::read_json(ss, _json);
    }
    catch (boost::property_tree::json_parser_error e)
    {
        throw std::invalid_argument("Error while parsing data");
    }
}

void JSONParser::write(std::string &str)
{
    try
    {
        std::stringstream ss("");
    
        boost::property_tree::write_json(ss, _json);
        str = ss.str();
    }
    catch (boost::property_tree::json_parser_error e)
    {
        throw std::invalid_argument("Error while parsing data");
    }
}

void JSONParser::clear()
{
    _json.clear();
}