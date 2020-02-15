#ifndef ILRD_RD734_COMMAND_HPP
#define ILRD_RD734_COMMAND_HPP

#include <netdb.h>

#include <boost/shared_ptr.hpp>

namespace ilrd
{

class Command
{
public:
    virtual ~Command() {}

    virtual void operator()(char *buffer) = 0;

    enum {SUCCESS = 0, FAIL = 1};

    const static size_t BLOCK_SIZE = 4096;
    const static size_t SEND_BLOCK_IDX_BYTE = 9;
    const static size_t SEND_DATA_BYTE = 17;
    const static size_t REPLY_STATUS_BYTE = 9;
    const static size_t REPLY_DATA_BYTE = 10;
};

} //namespace ilrd

#endif // ILRD_RD734_COMMAND_HPP