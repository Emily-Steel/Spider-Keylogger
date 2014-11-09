#ifndef _DISPATCHER_HPP_
# define _DISPATCHER_HPP_

# include <thread>

# include "ClientNetwork.hpp"
# include "APacket.hpp"
# include "ALog.hpp"

# define FILEPATH "log.json"

# define HOST "10.10.253.250"
# define PORT 2000

class Dispatcher
{
public:
    Dispatcher(const std::string &id);
    ~Dispatcher();
    
    void                    dispatch(const APacket &packet);
	void					handlePacket();
    std::vector<APacket *>  pollNetwork();
    
private:
    ClientNetwork           _net;
    std::unique_ptr<ALog>   _log;
	std::thread				_thread;
	std::string				_id;
};

#endif
