#ifndef	SPIDER_H
# define SPIDER_H

#include <memory>

#include "ICircularBuffer.hpp"
#include "ASocket.hpp"

class Spider
{
  constexpr static unsigned	bufferSize = 1024;

public:
  Spider();
  Spider(const std::shared_ptr<ASocket>& sock);
  virtual ~Spider(void) = default;
  Spider(const Spider& other) = delete;
  Spider&	operator=(const Spider& other) = delete;

  void		setSocket(const std::shared_ptr<ASocket>& sock);
  const std::shared_ptr<ASocket>&	getSocket(void) const;
  /*std::unique_ptr<ICircularBuffer>	&getReadBuf(void);
  std::unique_ptr<ICircularBuffer>	&getWriteBuf(void);*/

  bool		isHandshakeDone(void) const;

  void		onRead(const ASocket::t_bytes &buffer);
  void		onWrite(std::size_t size);

private:
  bool	_handshake_done;

  std::unique_ptr<ICircularBuffer> _read;
  std::unique_ptr<ICircularBuffer> _write;
  std::shared_ptr<ASocket>		  _socket;
};

#endif /* SPIDER_H */
