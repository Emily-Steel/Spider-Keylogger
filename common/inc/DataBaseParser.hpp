#ifndef _DATABASE_PARSER_HPP_
# define _DATABASE_PARSER_HPP_

#include "IReadable.hpp"
#include <map>

class DataBaseParser : public IReadable {

public:
    DataBaseParser();
    ~DataBaseParser();

    void put(const std::string &key, const std::string &value) override;
    void put(const std::string &key, const int &value) override;
    void put(const std::string &key, const short &value) override;
    void put(const std::string &key, const char &value) override;

    void get(const std::string &key, std::string &value) override;
    void get(const std::string &key, int &value) override;
    void get(const std::string &key, short &value) override;
    void get(const std::string &key, char &value) override;

    void read(std::string &str) override;
    void write(std::string &str) override;

    void clear() override;

private:
    std::map<std::string, std::string> _map;
};

#endif