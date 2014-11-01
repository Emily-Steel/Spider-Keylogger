#ifndef _SERVER_HPP_
# define _SERVER_HPP_

#include <string>
#include <thread>
#include <atomic>
#include <memory>
#include <cstdint>

#include "ALog.hpp"
#include "APacket.hpp"

class Server {
public:
    static constexpr const char* defaultLogPath = "spiderDb.json";
    static const uint16_t defaultPort = 4569;

public:
    Server(const std::string &logPath = defaultLogPath, uint16_t port = defaultPort) noexcept;
    virtual ~Server() noexcept;

    bool run();
    void pollCallback (ALog *log, const std::string &clientId, APacket &packet);

private:
    void handleInput();

private:
    std::atomic<bool> _quit;
    std::thread _inputThread;
    std::unique_ptr<ALog> _log;
};

#endif
