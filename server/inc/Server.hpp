#ifndef _SERVER_HPP_
# define _SERVER_HPP_

#include <string>
#include <thread>
#include <memory>
#include <cstdint>

#include "ALog.hpp"
#include "APacket.hpp"

class Server {
public:
    static constexpr const char* defaultLogPath = "spiderDb.json";
    static const uint16_t defaultPort = 4569;

private:
    std::thread input_thread;
    std::unique_ptr<ALog> log;

public:
    Server(const std::string &logPath = defaultLogPath, uint16_t port = defaultPort);
    virtual ~Server();

    bool run();
    void pollCallback (ALog * log, const std::string &clientId, APacket &packet);

private:
    void handle_input();

};

#endif
