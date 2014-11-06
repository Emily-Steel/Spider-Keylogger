#include "BoostCircularBuffer.hpp"

#include <algorithm>

//AFactoryRegistration<ICircularBuffer, BoostCircularBuffer> boostCircularBufFactRegister("CircularBuffer");

BoostCircularBuffer::BoostCircularBuffer(size_t buffSize)
: _buff(buffSize)
{
}

void BoostCircularBuffer::pushData(const std::vector<std::uint8_t>& buffer)
{
    for (auto &i : buffer)
        _buff.push_back(i);
}

void BoostCircularBuffer::discardData(std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
        _buff.pop_front();
}