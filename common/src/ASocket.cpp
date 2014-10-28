#include <ASocket.hpp>

ASocket::ASocket(void) :
  _type(Type::NONE)
{

}

auto	ASocket::getType(void) const -> const Type&
{
  return _type;
}
