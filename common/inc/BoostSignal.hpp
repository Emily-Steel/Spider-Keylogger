#ifndef BOOST_SIGNAL_H
# define BOOST_SIGNAL_H

#include <thread>
#include <csignal>
#include <functional>

#include <boost/asio/io_service.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/error.hpp>

#include "ISignal.hpp"

class BoostSignal : public ISignal
{
public:
    BoostSignal(const std::function<void(int signal)>& signalHandlerFunc = [](int){});
    virtual ~BoostSignal();

    void addSignal(int sig) override;
    void rmSignal(int sig) override;
    void start() override;
    void stop() override;

private:
    void signalHandler(const boost::system::error_code& error, int signal_number);

private:
    std::function<void(int signal)> _signalHandler;
    std::thread _signalHandlingThread;
    boost::asio::io_service _ios;
    boost::asio::signal_set _signals;
};

#endif
