#ifndef _SERVER_HPP_
# define _SERVER_HPP_

#include <string>
#include <thread>
#include <memory>
#include <ALog.hpp>
#include "APacket.hpp"

class Server {
private:
    std::thread input_thread;
    std::unique_ptr<ALog> log;
    void handle_input();
public:
    virtual ~Server();
    Server(const std::string &logPath);
    bool run();
    void pollCallback (ALog * log, const std::string &clientId, APacket &packet);
};

#endif
