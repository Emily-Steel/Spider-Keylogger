#ifndef ICIRCULAR_BUFFER_H
#define ICIRCULAR_BUFFER_H

#include <vector>

#include "AFactory.hpp"

class ICircularBuffer
{
public:
    virtual ~ICircularBuffer() = default;

    virtual void pushData(const std::vector<std::uint8_t>& buffer) = 0;
    virtual void discardData(std::size_t size) = 0;

};

#endif