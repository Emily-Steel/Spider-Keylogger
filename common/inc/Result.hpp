#ifndef _RESULT_HPP_
# define _RESULT_HPP_

# include "APacket.hpp"

class Result: public APacket
{
    public:
        Result(PacketType type);
        Result(PacketType type, char success);
        ~Result();
        
        virtual std::vector<char> to_bytes();
        virtual std::string to_readable();
        virtual void from_bytes(const std::vector<char> &bytes);
        virtual void from_readable(const std::string &data);
        
        void print();
        
    private:
        char _success;
};

#endif
