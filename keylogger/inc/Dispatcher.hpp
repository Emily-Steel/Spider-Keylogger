#ifndef _DISPATCHER_HPP_
# define _DISPATCHER_HPP_

# include <thread>

# include "APacket.hpp"
# include "ALog.hpp"
# include "ClientNetwork.hpp"

# define FILEPATH "log.json"

# define HOST "10.10.253.251"
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
	std::thread				_t;
};

#endif
