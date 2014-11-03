#include "Server.hpp"

#include <boost/filesystem.hpp>
#include <functional>

#include "FileLog.hpp"
#include "DataBaseLog.hpp"
#include "BoostSignal.hpp"

Server::Server(const std::string &logPath, uint16_t port) noexcept
: _quit(false), _network(port)
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

    _signalHandler = std::unique_ptr<ISignal>(new BoostSignal(std::bind(&Server::handleSignals, this, std::placeholders::_1)));
    _signalHandler->addSignal(SIGINT);
    _signalHandler->addSignal(SIGTERM);
    _signalHandler->addSignal(SIGQUIT);
}

Server::~Server() noexcept
{
    _inputThread.detach();
    if (_log->isGood())
        _log->close();
}

void Server::run() {
    if (!_log->isGood())
        throw std::runtime_error("Database file isn't ready.");
    _inputThread = std::thread(&Server::handleInput, this);
    _signalHandler->start();

    while (!_quit)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "b" << std::endl;
    }
    std::cout << "Server shutdown." << std::endl;
}

void Server::handleInput() {
    try {
        std::string line;
        while (std::getline(std::cin, line))
        {
            try {
                std::cout << "Command: " << line << std::endl;
            }
            catch (std::exception& e)
            {
                std::cerr << line << " throwed exception: " << e.what() << std::endl;
            }
        }
        _quit = true;
    }
    catch (std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
}

void Server::handleSignals(int sig) {
    std::cout << "Received signal " << sig << std::endl;
    if (sig == SIGINT || sig == SIGTERM || sig == SIGQUIT)
        _quit = true;
}

void Server::pollCallback(const std::string &clientId, APacket &packet) {
    std::cout << "CallBack on: " << clientId << std::endl;
    (void)packet;
}
