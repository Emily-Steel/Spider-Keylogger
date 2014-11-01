#include <iostream>
#include <stdexcept>
#include <boost/filesystem.hpp>

#include "FileLog.hpp"
#include "DataBaseLog.hpp"
#include "Server.hpp"

Server::Server(const std::string &logPath, uint16_t port) noexcept
: _quit(false)
{
    std::string dbext = boost::filesystem::extension(logPath);

    if (dbext == ".json")
        _log = std::unique_ptr<ALog>(new FileLog());
    else if (dbext == ".db")
        _log = std::unique_ptr<ALog>(new DataBaseLog());
    else
        throw std::runtime_error("Bad db extension.");

    std::cout << "Opening " << logPath << std::endl;
    _log->open(logPath);
}

Server::~Server() noexcept
{
    if (_inputThread.joinable())
        _inputThread.join();
    if (_log->isGood())
        _log->close();
}

bool Server::run() {
    if (!_log->isGood())
        throw std::runtime_error("Database file isn't ready.");
    _inputThread = std::thread(&Server::handleInput, this);
    while (!_quit.load(std::memory_order_relaxed))
    {

    }
    std::cout << "Server shutdown." << std::endl;
    return true;
}

void Server::handleInput() {
    try {
        std::string lign;

        while (std::getline(std::cin, lign))
        {
            std::cout << "Command: " << lign << std::endl;
        }

    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    _quit.store(true, std::memory_order_relaxed);
}

void Server::pollCallback(ALog *log, const std::string &clientId, APacket &packet) {
    (void)log;
    (void)clientId;
    (void)packet;
}
