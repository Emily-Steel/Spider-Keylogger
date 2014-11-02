#ifndef _DATABASE_PARSER_HPP_
# define _DATABASE_PARSER_HPP_

#include "IReadable.hpp"
#include <map>

class DataBaseParser : public IReadable {

public:
    DataBaseParser();
    ~DataBaseParser();

    virtual void put(const std::string &key, const std::string &value);
    virtual void put(const std::string &key, const int &value);
    virtual void put(const std::string &key, const short &value);
    virtual void put(const std::string &key, const char &value);

    virtual void get(const std::string &key, std::string &value);
    virtual void get(const std::string &key, int &value);
    virtual void get(const std::string &key, short &value);
    virtual void get(const std::string &key, char &value);

    virtual void read(std::string &);
    virtual void write(std::string &);

    virtual void clear();

private:
    std::map<std::string, std::string> _map;
};

#endif