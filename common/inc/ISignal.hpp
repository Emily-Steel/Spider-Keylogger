#ifndef ISIGNAL_H
# define ISIGNAL_H

class ISignal
{
public:

    virtual ~ISignal() = default;

    virtual void addSignal(int sig) = 0;
    virtual void rmSignal(int sig) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;

};

#endif