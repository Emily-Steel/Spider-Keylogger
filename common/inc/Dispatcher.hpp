#ifndef _DISPATCHER_HPP_
# define _DISPATCHER_HPP_

# include <thread>

# include "ClientNetwork.hpp"
# include "APacket.hpp"
# include "ALog.hpp"

# define FILEPATH "log.json"

# define HOST "10.10.253.238"
# define PORT 6060

class Dispatcher
{
public:
    Dispatcher();
    ~Dispatcher();
    
    void                    dispatch(const APacket &packet);
	void					handlePacket();
    std::vector<APacket *>  pollNetwork();
    
private:
	bool					_connect;
    ClientNetwork           _net;
    std::unique_ptr<ALog>   _log;
	std::thread				_thread;
};

#endif
