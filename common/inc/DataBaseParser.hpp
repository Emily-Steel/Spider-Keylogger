#ifndef _DATABASE_PARSER_HPP_
# define _DATABASE_PARSER_HPP_

#include "IReadable.hpp"
#include <map>

class DataBaseParser : public IReadable {

public:
    DataBaseParser();
    ~DataBaseParser();

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

    void read(std::string &str) override;
    void write(std::string &str) override;

    void clear() override;

private:
    std::map<std::string, std::string> _map;
};

#endif