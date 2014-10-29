#include "DataBaseLog.hpp"

DataBaseLog::DataBaseLog() {
    _sqlCreateKeyStroke =  "CREATE TABLE IF NOT EXISTS KEY_STROKE("  \
                  "NAME           TEXT    NOT NULL," \
                  "AGE            INT     NOT NULL," \
                  "ADDRESS        CHAR(50)," \
                  "SALARY         REAL );";
    _sqlCreateMouseClick =  "CREATE TABLE IF NOT EXISTS MOUSE_CLICK("  \
                  "NAME           TEXT    NOT NULL," \
                  "AGE            INT     NOT NULL," \
                  "ADDRESS        CHAR(50)," \
                  "SALARY         REAL );";
}

DataBaseLog::~DataBaseLog() {

}

void DataBaseLog::open(std::string const & path){
    int ret = sqlite3_open(path.c_str(), &_sqlDataBase);
    char *sqlErrMsg = NULL;
    if (ret != SQLITE_OK)
    {
        std::cerr << "Error while openenig \"" + path + "\"" << std::endl;
        std::cerr << sqlite3_errmsg(_sqlDataBase) << std::endl;
        _good = false;
    }
    ret = sqlite3_exec(_sqlDataBase, _sqlCreateKeyStroke.c_str(), nullptr, nullptr, &sqlErrMsg);
    if (ret != SQLITE_OK)
    {
        std::cerr << "Error while creating key_stroke table" << std::endl;
        std::cerr << "SQL error: " + std::string(sqlErrMsg) << std::endl;
        sqlite3_free(sqlErrMsg);
        _good = false;
    }
    ret = sqlite3_exec(_sqlDataBase, _sqlCreateMouseClick.c_str(), nullptr, nullptr, &sqlErrMsg);
    if (ret != SQLITE_OK)
    {
        std::cerr << "Error while creating mouse_click table" << std::endl;
        std::cerr << "SQL error: " + std::string(sqlErrMsg) << std::endl;
        sqlite3_free(sqlErrMsg);
        _good = false;
    }

    if (_good) {
        std::cout << "Table created successfully" << std::endl;
    }
}

void DataBaseLog::close() {
    sqlite3_close(_sqlDataBase);
}

bool DataBaseLog::isGood() const {
    return _good;
}

void DataBaseLog::insert(APacket const &param, std::string const &id) {

}

std::vector<APacket *> DataBaseLog::dump() {
}
