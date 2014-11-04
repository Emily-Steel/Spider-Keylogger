#ifndef	SPIDER_H
# define SPIDER_H

# include <memory>

# include <boost/circular_buffer.hpp>

# include "ASocket.hpp"

class Spider
{
  constexpr static unsigned	bufferSize = 1024;

public:
  Spider();
  Spider(std::shared_ptr<ASocket> sock);
  virtual ~Spider(void) = default;
  Spider(const Spider& other) = delete;
  Spider&	operator=(const Spider& other) = delete;

  void		setSocket(std::shared_ptr<ASocket> sock);
  std::shared_ptr<ASocket>	getSocket(void) const;
  boost::circular_buffer<std::uint8_t>	&getReadBuf(void);
  boost::circular_buffer<std::uint8_t>	&getWriteBuf(void);

  bool		isHandshakeDone(void) const;

  void		onRead(ASocket::t_bytes &buffer, std::size_t size);
  void		onWrite(std::size_t size);

private:
  bool	_handshake_done;

  boost::circular_buffer<std::uint8_t>	_read;
  boost::circular_buffer<std::uint8_t>	_write;
  std::shared_ptr<ASocket>		_socket;
};

#endif /* SPIDER_H */
