#include "BoostListenSocket.hpp"

#include "BoostConnectSocket.hpp"

//AFactoryRegistration<IListenSocket, BoostListenSocket> boostListenSocketFactReg("BoostListenSocket");

BoostListenSocket::BoostListenSocket(const std::shared_ptr<boost::asio::io_service>& ios)
: _ios(ios), _acceptor(*_ios)
{

}

BoostListenSocket::~BoostListenSocket()
{

}

void	BoostListenSocket::bind(const std::string &addr, uint16_t port)
{
    boost::asio::ip::address baddr = boost::asio::ip::address::from_string(addr);

    _acceptor.open(familyFromAddr(baddr));
    _acceptor.bind({baddr, port});
}

void	BoostListenSocket::listen(int backlog)
{
    _acceptor.listen(backlog);
}

std::shared_ptr<IConnectSocket>	BoostListenSocket::accept()
{
    auto sock = new BoostConnectSocket(*_ios);

    _acceptor.accept(sock->socket());
    return std::shared_ptr<IConnectSocket>(sock);
}

void BoostListenSocket::async_accept(const t_acceptCallback& callback)
{
    auto sock = new BoostConnectSocket(*_ios);

    std::function<void(const boost::system::error_code &)> f(std::bind(&BoostListenSocket::onAccept, this,
            callback, std::placeholders::_1, std::shared_ptr<IConnectSocket>(sock)));
    _acceptor.async_accept(sock->socket(), f);
}

void	BoostListenSocket::onAccept(const t_acceptCallback& callback,
        const boost::system::error_code &ec,
        const std::shared_ptr<IConnectSocket>& sock)
{
    if (!ec)
        callback(sock);
    else
        std::cerr << "Error onAccept " << ec.message() << std::endl;
}

void BoostListenSocket::poll()
{
    _ios->poll();
}

void BoostListenSocket::start()
{
    _ios->run();
}

void BoostListenSocket::stop()
{
    _ios->stop();
}

boost::asio::ip::tcp BoostListenSocket::familyFromAddr(const boost::asio::ip::address &addr) const {
    if (addr.is_v4())
        return boost::asio::ip::tcp::v4();
    else if (addr.is_v6())
        return boost::asio::ip::tcp::v6();
    throw std::runtime_error("Family address is not v4 nor v6.");
}
