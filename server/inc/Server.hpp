#ifndef _SERVER_HPP_
# define _SERVER_HPP_

#include <string>
#include <thread>
#include <atomic>
#include <memory>
#include <cstdint>

#include "ISignal.hpp"
#include "ALog.hpp"
#include "Network.hpp"

class Server {
public:
    static constexpr const char* defaultLogPath = "spiderDb.json";
    static const uint16_t defaultPort = 4569;

public:
    Server(const std::string &logPath = defaultLogPath, uint16_t port = defaultPort) noexcept;
    virtual ~Server() noexcept;

    void run();

private:
    void handleInput();
    void handleSignals(int sig);

private:
    std::atomic_bool _quit;
    std::thread _inputThread;
    std::unique_ptr<ALog> _log;
    std::unique_ptr<Network> _network;
    std::unique_ptr<ISignal> _signalHandler;
};

#endif
