#include <iostream>
#include <stdexcept>
#include <boost/filesystem.hpp>

#include "FileLog.hpp"
#include "DataBaseLog.hpp"
#include "Server.hpp"

Server::Server(const std::string &logPath, uint16_t port)
{
    std::string dbext = boost::filesystem::extension(logPath);

    if (dbext == ".json")
    {
           std::cout << "JSON FILE" << std::endl;
           std::unique_ptr<ALog> filelog(new FileLog());
           log = std::move(filelog);
    }
    else if (dbext == ".db")
    {
        std::cout << "DATABASE FILE" << std::endl;
        std::unique_ptr<ALog> dataBaseLog(new DataBaseLog());
        log = std::move(dataBaseLog);
    }
    else
        throw std::runtime_error("Bad db extension.");
}

Server::~Server() {
}

bool Server::run() {
    return false;
}

void Server::handle_input() {

}

void Server::pollCallback(ALog *log, const std::string &clientId, APacket &packet) {
    (void)log;
    (void)clientId;
    (void)packet;
}
