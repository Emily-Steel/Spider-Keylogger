#ifndef	ASOCKET_H
# define ASOCKET_H

# include <memory>
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

  ASocket(void);
  virtual ~ASocket(void) = default;
  ASocket(const ASocket& other) = delete;
  ASocket&	operator=(const ASocket& other) = delete;

  // pure methods
  virtual ASocket&	operator<<(const APacket& packet) = 0;
  virtual ASocket                   &	operator>>(APacket& packet) = 0;
  virtual std::size_t write(void *data, std::size_t size) = 0;
  virtual std::size_t read(std::string &buffer, std::size_t size) = 0;

  virtual bool              connect(const std::string& address, unsigned short port) = 0;
  virtual void				bind(const std::string &addr, uint16_t port) = 0;
  virtual void				listen(int backlog) = 0;
  virtual std::shared_ptr<ASocket>	accept(void) = 0;

  const Type&         getType(void) const;

protected:
  Type				_type;
};

#endif /* ASOCKET_H */
