#include "Server.hpp"

#include <algorithm>
#include <functional>

#include <boost/filesystem.hpp>

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
    _signalHandler->addSignal(SIGPIPE);
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

    std::string			bcStr = "Hello little Spider :)!";
    std::vector<std::uint8_t>	bc(bcStr.length());
    std::chrono::steady_clock::time_point last(std::chrono::steady_clock::now());

    std::copy(bcStr.begin(), bcStr.end(), bc.begin());
    while (!_quit)
    {
      _network.poll_clients();
      std::chrono::steady_clock::time_point now(std::chrono::steady_clock::now());
      if (std::chrono::duration_cast<std::chrono::seconds>(now - last).count() > 2) {
	last = now;
	_network.broadcast(bc, bc.size());
      }
    }
    std::cout << "Server shutdown." << std::endl;
}

void Server::handleInput() {
    try {
        std::string line;
        while (!_quit && std::getline(std::cin, line))
        {
            try {
                std::cout << "Command: " << line << std::endl;
                if (line == "quit")
                    _quit = true;
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
