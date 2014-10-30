#ifndef _DATABASELOG_HPP_
# define _DATABASELOG_HPP_

# include <APacket.hpp>
# include <ALog.hpp>
# include <sqlite3.h>
# include "DataBaseParser.hpp"

class DataBaseLog : public ALog {
public:
    DataBaseLog();
    ~DataBaseLog();

    virtual void open(const std::string &path);
    virtual void close();
    virtual bool isGood() const;
    virtual void insert(const APacket &, const std::string &id);
    virtual std::vector<APacket *> dump();

private:
    std::vector<APacket *> getAllRowFromTable(std::string tableName);
    APacket *rowToAPacket();
    sqlite3 *_sqlDataBase;
    bool _good = true;
    std::string _sqlCreateTable;
    DataBaseParser _dataBaseParser;
};

#endif
