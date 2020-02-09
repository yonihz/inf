#include <utility>

#include "fd_listener.hpp"
#include "singleton.hpp"
#include "logger.hpp"

namespace ilrd
{

void InitFDSets(
    FDListener::FDVector& fds,
    fd_set *read,
    fd_set *write, 
    fd_set *except,
    int *fdmax);

void CreateReadyFDVector(
    FDListener::FDVector *ready_fds,
    fd_set *read,
    fd_set *write, 
    fd_set *except,
    int fdmax);

const boost::chrono::milliseconds FDListener::s_timeout(2000);

FDListener::FDVector FDListener::Wait(FDListener::FDVector& fds_)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    int status = 0, fdmax = 0;
    fd_set read_fds, write_fds, except_fds;
    FDListener::FDVector ready_fds;
    struct timeval timev;

    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    FD_ZERO(&except_fds);

    timev.tv_sec = 0;
    timev.tv_usec = FDListener::s_timeout.count() * 1000;

    InitFDSets(fds_, &read_fds, &write_fds, &except_fds, &fdmax);
    status = select(fdmax + 1, &read_fds, &write_fds, &except_fds, &timev);

    if (status == 0)
    {
        logger.Log(Logger::DEBUG, "select timeout reached, retrying...\n");
    }

    if (-1 == status)
    {
        logger.Log(Logger::ERROR, "select: ");
        logger.Log(Logger::ERROR, strerror(errno));
        logger.Log(Logger::ERROR, "\n");
        return ready_fds;
    }

    CreateReadyFDVector(&ready_fds, &read_fds, &write_fds, &except_fds, fdmax);

    return ready_fds;
}

void InitFDSets(
    FDListener::FDVector &fds,
    fd_set *read,
    fd_set *write, 
    fd_set *except,
    int *fdmax)
{
    for (FDListener::FDVector::iterator it = fds.begin() ; it != fds.end(); ++it)
    {
        *fdmax = (it->first > *fdmax) ? (it->first) : (*fdmax);
        
        switch (it->second)
        {
            case FDListener::READ:
            {
                FD_SET(it->first, read);
                break;
            }
            case FDListener::WRITE:
            {
                FD_SET(it->first, write);
                break;
            }
            case FDListener::EXCEPT:
            {
                FD_SET(it->first, except);
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

void CreateReadyFDVector(
    FDListener::FDVector *ready_fds,
    fd_set *read,
    fd_set *write, 
    fd_set *except,
    int fdmax)
{
    FDListener::Mode mode;

    for (int i = 0; i <= fdmax; ++i)
    {
        if (FD_ISSET(i, read))
        {
            mode =  FDListener::READ;
        }
        else if (FD_ISSET(i, write))
        {
            mode =  FDListener::WRITE;
        }
        else if (FD_ISSET(i, except))
        {
            mode =  FDListener::EXCEPT;
        }
        else
        {
            continue;
        }

        ready_fds->push_back(std::make_pair(i, mode));
    }
}

} // namespace ilrd