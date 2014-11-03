#ifndef	ASOCKET_H
# define ASOCKET_H

# include <memory>
# include <functional>
# include <cstdint>

# include "APacket.hpp"

# define SIZEREAD 512

class ASocket
{
public:
  enum class Type
    {
      NONE,
      PASSIVE,
      ACTIVE
    };

  typedef std::vector<std::uint8_t>			t_bytes;
  typedef std::function<void(std::size_t)>		t_writeCallback;
  typedef std::function<void(t_bytes &, std::size_t)>	t_readCallback;

  ASocket(void);
  virtual ~ASocket(void) = default;
  ASocket(const ASocket& other) = delete;
  ASocket	&operator=(const ASocket& other) = delete;

  // pure methods
  virtual ASocket	&operator<<(const APacket& packet) = 0;
  virtual ASocket	&operator>>(APacket& packet) = 0;
  virtual std::size_t	write(void *data, std::size_t size) = 0;
  virtual std::size_t	read(t_bytes &buffer, std::size_t size) = 0;
  virtual void		async_write(void *data, std::size_t size, t_writeCallback &callback) = 0;
  virtual void		async_read(t_bytes &buffer, t_readCallback &callback) = 0;

  virtual bool				connect(const std::string& address, unsigned short port) = 0;
  virtual void				bind(const std::string &addr, uint16_t port) = 0;
  virtual void				listen(int backlog) = 0;
  virtual std::shared_ptr<ASocket>	accept(void) = 0;

  const Type&		getType(void) const;

protected:
  Type			_type;
};

#endif /* ASOCKET_H */
