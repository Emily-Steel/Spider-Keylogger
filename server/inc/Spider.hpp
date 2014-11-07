#ifndef	SPIDER_H
# define SPIDER_H

#include <memory>

#include "ICircularBuffer.hpp"
#include "IConnectSocket.hpp"

class Spider
{
  constexpr static unsigned	bufferSize = 1024;

public:
  Spider();
  Spider(const std::shared_ptr<IConnectSocket>& sock);
  virtual ~Spider(void) = default;
  Spider(const Spider& other) = delete;
  Spider&	operator=(const Spider& other) = delete;

  void		setSocket(const std::shared_ptr<IConnectSocket>& sock);
  const std::shared_ptr<IConnectSocket>&	getSocket(void) const;
  /*std::unique_ptr<ICircularBuffer>	&getReadBuf(void);
  std::unique_ptr<ICircularBuffer>	&getWriteBuf(void);*/

  bool		isHandshakeDone(void) const;

  void		onRead(const std::vector<uint8_t>& buffer);
  void		onWrite(std::size_t size);

private:
  bool	_handshake_done;

  std::unique_ptr<ICircularBuffer> _read;
  std::unique_ptr<ICircularBuffer> _write;
  std::shared_ptr<IConnectSocket>		  _socket;
};

#endif /* SPIDER_H */
