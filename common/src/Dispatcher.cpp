#include "Dispatcher.hpp"
#include "FileLog.hpp"

Dispatcher::Dispatcher(const std::string &id)
	: _log(new FileLog()), _id(id)
{
	_log->open(FILEPATH);
	_log->setParser(new JSONParser());

	_thread = std::thread(&Dispatcher::handlePacket, this);
}

Dispatcher::~Dispatcher()
{
	_thread.join();
}

void                    Dispatcher::dispatch(const APacket &packet)
{
	std::cout << "WRITE";
	if (_net.isConnected())
	{
		std::cout << " NET" << std::endl;
		_net << packet;
	}
	else
	{
		std::cout << " LOG" << std::endl;
		_log->insert(packet, "");
	}
}

void                    Dispatcher::handlePacket()
{
	for (;;)
	{
		std::cout << "HANDLE PACKET" << std::endl;
		if (_net.isConnected())
		{
/*				APacket *packet;

				_net >> *packet;
				if (dynamic_cast<HandshakeResult *>(packet) != NULL)
				_connect = true;*/
		}
		else
		{
			if (_net.connect(PORT, HOST, _id))
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
