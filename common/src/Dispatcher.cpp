#include "Dispatcher.hpp"
#include "FileLog.hpp"

Dispatcher::Dispatcher(const std::string &id)
	: _log(new FileLog()), _id(id)
{
	_log->open(FILEPATH);
	_log->setParser(std::shared_ptr<IReadable>(new JSONParser()));

	_thread = std::thread(&Dispatcher::handlePacket, this);
}

Dispatcher::~Dispatcher()
{
	_thread.join();
}

void                    Dispatcher::dispatch(const APacket &packet)
{
	if (_net.isConnected())
		_net << packet;
	else
		_log->insert(packet, "");
}

void                    Dispatcher::handlePacket()
{
	for (;;)
	{
		if (!_net.isConnected())
		{
			if (_net.connect(PORT, HOST, _id))
			{
				std::cout << "CONNECTED" << std::endl;
				std::vector<APacket *> dump = _log->dump();

				if (!dump.empty())
					for (auto it : dump)
						_net << (*it);
			}
		}
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

std::vector<APacket *>  Dispatcher::pollNetwork()
{
	std::vector<APacket *> ret;

	return (ret);
}
