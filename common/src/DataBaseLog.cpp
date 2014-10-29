#include "DataBaseLog.hpp"

DataBaseLog::DataBaseLog() {
    _sqlCreateKeyStroke =  "CREATE TABLE IF NOT EXISTS KEY_STROKE("  \
                  "ID           TEXT    NOT NULL);";

    _sqlCreateMouseClick =  "CREATE TABLE IF NOT EXISTS MOUSE_CLICK("  \
                  "ID           TEXT    NOT NULL);";
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
    std::vector<APacket *> allTablesRow;

    allTablesRow = getAllRowFromTable("KEY_STROKE");
    return allTablesRow;
}

std::vector<APacket *> DataBaseLog::getAllRowFromTable(std::string tableName) {
    std::string query = "SELECT * FROM " + tableName;
    std::vector<APacket *> allRow;
    sqlite3_stmt *stmt;
    int ret;

    ret = sqlite3_prepare(_sqlDataBase, query.c_str(), query.size() + 1, &stmt, NULL);
    if (ret != SQLITE_OK) {
        _good = false;
        std::cerr << "Error while getting all row from \"" + tableName + "\"" << std::endl;
        return allRow;
    }

    while ((ret = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char * text;
        text  = sqlite3_column_text (stmt, 0);
        std::cout << text << std::endl;
    }
    if (ret != SQLITE_DONE) {
        _good = false;
        std::cerr << "Error while getting all row from \"" + tableName + "\"" << std::endl;
        return allRow;
    }
    sqlite3_finalize(stmt);
    return allRow;
}


APacket *DataBaseLog::rowToAPacket() {

}
