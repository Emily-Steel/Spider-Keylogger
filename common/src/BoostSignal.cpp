#include "BoostSignal.hpp"

BoostSignal::BoostSignal(const std::function<void(int signal)>& signalHandlerFunc)
: _signalHandler(signalHandlerFunc), _signals(_ios)
{
}

BoostSignal::~BoostSignal() {
    stop();
}

void BoostSignal::addSignal(int sig) {
    _signals.add(sig);
}

void BoostSignal::rmSignal(int sig) {
    _signals.remove(sig);
}

void BoostSignal::start() {
    _signals.async_wait(std::bind(static_cast<void(BoostSignal::*)(const boost::system::error_code&, int)>(&BoostSignal::signalHandler), this, std::placeholders::_1, std::placeholders::_2));
    auto runner = std::bind(static_cast<std::size_t(boost::asio::io_service::*)()>(&boost::asio::io_service::run), std::ref(_ios));
    _signalHandlingThread = std::thread(runner);
}

void BoostSignal::stop() {
    _ios.stop();
    if (_signalHandlingThread.joinable())
        _signalHandlingThread.join();
}

void BoostSignal::signalHandler(const boost::system::error_code&, int signal_number)
{
    _signalHandler(signal_number);
    _signals.async_wait(std::bind(static_cast<void(BoostSignal::*)(const boost::system::error_code&, int)>(&BoostSignal::signalHandler), this, std::placeholders::_1, std::placeholders::_2));
}
