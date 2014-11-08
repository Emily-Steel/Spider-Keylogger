#ifndef	SPIDER_H
# define SPIDER_H

#include <memory>
#include <string>

#include "ICircularBuffer.hpp"
#include "IConnectSocket.hpp"

class Spider
{
  constexpr static unsigned	bufferSize = 1024;

public:
  Spider(const std::shared_ptr<IConnectSocket>& sock);
  virtual ~Spider(void) = default;
  Spider(const Spider& other) = delete;
  Spider&	operator=(const Spider& other) = delete;

  const std::shared_ptr<IConnectSocket>&	getSocket(void) const;
  /*std::unique_ptr<ICircularBuffer>	&getReadBuf(void);
  std::unique_ptr<ICircularBuffer>	&getWriteBuf(void);*/

  bool		isHandshakeDone(void) const;

  void      read();
  void      write() const;

  void		onRead(const std::vector<uint8_t>& buffer);
  void		onWrite(std::size_t size);

  const std::string& getIdentity() const {return _identity;};
  void setIdentity(const std::string& id) {_identity = id;};

private:
  bool	_handshake_done;
  std::string _identity;

  IConnectSocket::t_writeCallback _writeCallback;
  IConnectSocket::t_readCallback _readCallback;
  std::unique_ptr<ICircularBuffer> _read;
  std::unique_ptr<ICircularBuffer> _write;
  std::shared_ptr<IConnectSocket> _socket;
  std::vector<uint8_t>    _buff;
  std::vector<uint8_t>    _buff2;
};

#endif /* SPIDER_H */
