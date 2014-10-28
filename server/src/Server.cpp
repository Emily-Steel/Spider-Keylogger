#include <iostream>
#include <FileLog.hpp>
#include <DataBaseLog.hpp>
#include "Server.hpp"

Server::Server(const std::string &logPath) {
    std::string fileName = "";
    size_t found;

    found = logPath.find_last_of("/\\");
    if (found != std::string::npos) {
        fileName = logPath.substr(found + 1);
    }
    else {
        fileName = logPath;
    }
    found = fileName.find_last_of(".");
    if (found != std::string::npos) {
        std::string type = fileName.substr(found + 1);
        if (type.compare("json") == 0) {
            std::cout << "JSON FILE" << std::endl;
            std::unique_ptr<FileLog> filelog(new FileLog());
            log = std::move(filelog);
            log->open(logPath);
            log->close();
        }
        else if (type.compare("db") == 0) {
            std::cout << "DATABASE FILE" << std::endl;
            std::unique_ptr<DataBaseLog> dataBaseLog(new DataBaseLog());
            log = std::move(dataBaseLog);
            log->open(logPath);
            log->close();
        }
        else {
            throw std::invalid_argument("Invalid log file type [" + fileName + "]" + "\n" + "File type must be .db or .json");
        }
    }
    else {
        throw std::invalid_argument("Invalid log file type [" + fileName + "]" + "\n" + "File type must be .db or .json");
    }
}

Server::~Server() {
}

bool Server::run() {
    return false;
}

void Server::handle_input() {

}

void Server::pollCallback(ALog *log, const std::string &clientId, APacket &packet) {

}
