#include <utility> // std::make_pair

#include "fd_listener.hpp"
#include "singleton.hpp"
#include "logger.hpp"

namespace ilrd
{

void InitFDSets(FDListener::FDVector& fds, fd_set *fd_sets, int *fdmax);

void CreateReadyFDVector(FDListener::FDVector *ready_fds, fd_set *fd_sets, int fdmax);

const boost::chrono::milliseconds FDListener::s_timeout(2000);

FDListener::FDVector FDListener::Wait(FDListener::FDVector& fds_)
{
    Logger &logger = *(Singleton<Logger>::Instance());
    FDListener::FDVector ready_fds;

    fd_set fd_sets[FDListener::MAX_MODE];
    FD_ZERO(&fd_sets[FDListener::READ]);
    FD_ZERO(&fd_sets[FDListener::WRITE]);
    FD_ZERO(&fd_sets[FDListener::EXCEPT]);

    struct timeval timev;
    timev.tv_sec = 0;
    timev.tv_usec = FDListener::s_timeout.count() * 1000;

    int fdmax = 0;
    InitFDSets(fds_, fd_sets, &fdmax);

    int status = 0;
    status = select(
        fdmax + 1, 
        &fd_sets[FDListener::READ], 
        &fd_sets[FDListener::WRITE], 
        &fd_sets[FDListener::EXCEPT], 
        &timev);

    if (0 == status)
    {
        logger.Log(Logger::DEBUG, "select timeout reached, retrying...\n");
    }

    if (-1 == status)
    {
        logger.Log(Logger::ERROR,"select: " + std::string(strerror(errno)) + "\n");
        return ready_fds;
    }

    CreateReadyFDVector(&ready_fds, fd_sets, fdmax);

    return ready_fds;
}

void InitFDSets(FDListener::FDVector& fds, fd_set *fd_sets, int *fdmax)
{
    FDListener::FDVector::iterator it;
    FDListener::FDVector::iterator it_end = fds.end();
    for (it = fds.begin() ; it != it_end; ++it)
    {
        *fdmax = (it->first > *fdmax) ? (it->first) : (*fdmax);
        FD_SET(it->first, &fd_sets[it->second]);
    }
}

void CreateReadyFDVector(FDListener::FDVector *ready_fds, fd_set *fd_sets, int fdmax)
{
    FDListener::Mode mode;

    for (int i = 0; i <= fdmax; ++i)
    {
        if (FD_ISSET(i, &fd_sets[FDListener::READ]))
        {
            mode =  FDListener::READ;
        }
        else if (FD_ISSET(i, &fd_sets[FDListener::WRITE]))
        {
            mode =  FDListener::WRITE;
        }
        else if (FD_ISSET(i, &fd_sets[FDListener::EXCEPT]))
        {
            mode =  FDListener::EXCEPT;
        }
        else
        {
            continue;
        }

        ready_fds->push_back(FDListener::ModeAndFD(i, mode));
    }
}

} // namespace ilrd