#include <iostream>
#include <Server.hpp>

#include "ASocket.hpp"
#include "SocketFactory.hpp"
#include "JSONParser.hpp"

#include "KeyStroke.hpp"
#include "MouseClick.hpp"
#include "ScreenShotRequest.hpp"
#include "KillRequest.hpp"
#include "KillConfirm.hpp"
#include "HandshakeResult.hpp"
#include "ScreenShot.hpp"

int	main(void)
{
    Keystroke t1("salut");
    Keystroke t2;

    MouseClick a1(1, 2, 3);
    MouseClick a2;

    ScreenShotRequest b1;
    ScreenShotRequest b2;

    KillRequest c1;
    KillRequest c2;

    KillConfirm d1(5);
    KillConfirm d2;

    HandshakeResult e1(1);
    HandshakeResult e2;

    ScreenShot f1(1, "salut");
    ScreenShot f2;

    try
    {
        Server serv("toto.db");
    }
    catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    t2.from_bytes(t1.to_bytes());
    t2.print();

    std::cout << "--" << std::endl;
    
    a2.from_bytes(a1.to_bytes());
    a2.print();

    std::cout << "--" << std::endl;

    b2.from_bytes(b1.to_bytes());
    b2.print();
    
    std::cout << "--" << std::endl;

    c2.from_bytes(c1.to_bytes());
    c2.print();
    
    std::cout << "--" << std::endl;

    d2.from_bytes(d1.to_bytes());
    d2.print();
    
    std::cout << "--" << std::endl;

    e2.from_bytes(e1.to_bytes());
    e2.print();
    
    std::cout << "--" << std::endl;

    f2.from_bytes(f1.to_bytes());
    f2.print();

    std::cout << "--" << std::endl;

    std::cout << "Hello World!" << std::endl;
    
    std::string tmp = t1.to_readable();

    std::cout << tmp << std::endl;
    ASocket *socket = SocketFactory::getInstance().createSocket();

    if (socket->connect("127.0.0.1", 6060) == false)
        return (1);
    for (;;)
    {
        char data[] = "Hello World!\n";
        std::string r;

        if (socket->write(data, std::strlen(data)) == false)
            return (1);
        socket->read(r, 512);
        std::cout << r << std::endl;
    }
	return (0);
}
