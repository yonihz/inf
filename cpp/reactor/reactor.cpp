#include <utility> // std::make_pair

#include "reactor.hpp"

namespace ilrd
{

void Reactor::Run()
{
    m_is_running = true;
    
    while (m_is_running)
    {
        FDListener::FDVector master_fds;
        FDListener::FDVector ready_fds;

        std::map<FDListener::ModeAndFD, Reactor::ReactorFunction>::iterator it1;
        std::map<FDListener::ModeAndFD, Reactor::ReactorFunction>::iterator it1_end = m_fdToFuncs.end();
        for (it1 = m_fdToFuncs.begin(); it1 != it1_end; ++it1)
        {
            master_fds.push_back(it1->first);
        }

        ready_fds = FDListener::Wait(master_fds);

        FDListener::FDVector::iterator it2;
        FDListener::FDVector::iterator it2_end = ready_fds.end();
        for (it2 = ready_fds.begin(); it2 != it2_end; ++it2)
        {
            m_fdToFuncs[*it2]();
        }
    }
}

void Reactor::Stop()
{
    m_is_running = false;
}

void Reactor::AddFD(int fd_, Mode mode_, ReactorFunction func_)
{
    m_fdToFuncs.insert(
        std::make_pair(
            FDListener::ModeAndFD(fd_, static_cast<FDListener::Mode>(mode_)),
            func_));
}

void Reactor::RemoveFD(int fd_, Mode mode_)
{
    m_fdToFuncs.erase(
        FDListener::ModeAndFD(fd_, static_cast<FDListener::Mode>(mode_)));
}


} // namespace ilrd