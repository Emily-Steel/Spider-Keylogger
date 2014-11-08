#include "Server.hpp"

#include <algorithm>
#include <functional>

#include "IFileSystemHelper.hpp"
#include "AFactory.hpp"
#include "FileLog.hpp"
#include "DataBaseLog.hpp"
#include "BoostSignal.hpp"

Server::Server(const std::string &logPath, uint16_t port) noexcept
 : _quit(false), _network(port)
{
    std::unique_ptr<IFileSystemHelper> fileSystem = AFactory<IFileSystemHelper>::instance().create("BoostFileSystemHelper");

    std::string dbext = fileSystem->fileExtension(logPath);

    if (dbext == ".json")
        _log = std::unique_ptr<ALog>(new FileLog()); //AFactory<ALog>::instance().create("FileLog");
    else if (dbext == ".db")
        _log = std::unique_ptr<ALog>(new DataBaseLog()); //AFactory<ALog>::instance().create("DataBaseLog");
    else
        throw std::runtime_error("Bad db extension.");

    std::cout << "Opening " << logPath << std::endl;
    _log->open(logPath);

    //_signalHandler = AFactory<ISignal>::instance().create("BoostSignal");
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

    std::string			bcStr = "Hello little Spider :)!\n";
    std::vector<std::uint8_t>	bc(bcStr.length());
    std::chrono::steady_clock::time_point last(std::chrono::steady_clock::now());

    std::copy(bcStr.begin(), bcStr.end(), bc.begin());

    _network.run();
    std::cout << "Server shutdown." << std::endl;
}

void Server::handleInput() {
    try {
        std::string line;
        while (!_quit && std::getline(std::cin, line))
        {
            try {
                if (line == "quit")
                    _network.stop(); //_quit = true;
                else if (line == "help")
                    std::cout << "This is an help !" << std::endl;
                else if (line.compare(0, std::string("send ").size(), "send ") == 0)
                {
                    std::string	bcStr = line.substr(std::string("send ").size());
                    std::vector<std::uint8_t>	bc(bcStr.length());
                    std::copy(bcStr.begin(), bcStr.end(), bc.begin());
                    _network.broadcast(bc);
                }
            }
            catch (std::exception& e)
            {
                std::cerr << line << " throwed exception: " << e.what() << std::endl;
            }
        }
        _network.stop(); //_quit = true;
    }
    catch (std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
}

void Server::handleSignals(int sig) {
   // std::cout << "Received signal " << sig << std::endl;
    if (sig == SIGINT || sig == SIGTERM || sig == SIGQUIT)
        _network.stop(); //_quit = true;
}