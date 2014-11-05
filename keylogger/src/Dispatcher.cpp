#include "FileLog.hpp"
#include "Dispatcher.hpp"

Dispatcher::Dispatcher()
	: _connect(false), _log(new FileLog())
{
	_log->open(FILEPATH);
	_log->setParser(new JSONParser());

	_t = std::thread(&Dispatcher::handlePacket, this);
}

Dispatcher::~Dispatcher()
{
	_t.detach();
}

void                    Dispatcher::dispatch(const APacket &packet)
{
	std::cout << "WRITE" << std::endl;
    if (_connect)
        _net << packet;
	else
		_log->insert(packet, "");
}

void                    Dispatcher::handlePacket()
{
	for (;;)
	{
		std::cout << "HANDLE PACKET" << std::endl;
		if (_net.isConnected())
		{
			APacket *packet;

			_net >> *packet;
			if (dynamic_cast<HandshakeResult *>(packet) != NULL)
				_connect = true;
		}
		else
		{
			_connect = false;
			if (_net.connect(PORT, HOST))
				std::cout << "CONNECTED" << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

std::vector<APacket *>  Dispatcher::pollNetwork()
{
	std::vector<APacket *> ret;

	return (ret);
}
