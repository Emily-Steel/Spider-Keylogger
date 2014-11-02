#include <sstream>
#include "DataBaseParser.hpp"

DataBaseParser::DataBaseParser() {

}

DataBaseParser::~DataBaseParser() {

}

void DataBaseParser::put(const std::string &key, const std::string &value)
{
    _map[key] = value;
}

void DataBaseParser::put(const std::string &key, const int &value)
{
    std::stringstream ss("");

    ss << value;
    _map[key] = ss.str();
}

void DataBaseParser::put(const std::string &key, const short &value)
{
    std::stringstream ss("");

    ss << value;
    _map[key] = ss.str();
}

void DataBaseParser::put(const std::string &key, const char &value)
{
    std::stringstream ss("");

    ss << value;
    _map[key] = ss.str();
}

void DataBaseParser::get(const std::string &key, std::string &value)
{
    value = _map[key];
}

void DataBaseParser::get(const std::string &key, int &value)
{
    std::string str = _map[key];
    std::stringstream ss(str);

    ss >> value;
}

void DataBaseParser::get(const std::string &key, short &value)
{
    std::string str = _map[key];
    std::stringstream ss(str);

    ss >> value;
}

void DataBaseParser::get(const std::string &key, char &value)
{
    std::string str = _map[key];
    std::stringstream ss(str);

    ss >> value;
}

void DataBaseParser::read(std::string &)
{
}

void DataBaseParser::write(std::string &)
{
}

void DataBaseParser::clear()
{
    _map.clear();
}
