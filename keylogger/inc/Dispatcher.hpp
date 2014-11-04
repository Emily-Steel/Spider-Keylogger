#ifndef _DISPATCHER_HPP_
# define _DISPATCHER_HPP_

# include "APacket.hpp"
# include "ALog.hpp"
# include "ClientNetwork.hpp"

class Dispatcher
{
public:
    Dispatcher();
    ~Dispatcher();
    
    void                    dispatch(const APacket &packet);
    void                    handlePacket(APacket &packet);
    std::vector<APacket *>  pollNetwork();
    
private:
    ClientNetwork           _net;
    std::unique_ptr<ALog>   _log;
};

#endif
