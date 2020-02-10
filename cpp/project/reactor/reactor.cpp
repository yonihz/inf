#include <utility> // std::make_pair
#include <iostream>  //delete

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

        std::map<FDListener::ModeAndFD, Reactor::Function>::iterator it1;
        for (it1 = m_fdToFuncs.begin(); it1 != m_fdToFuncs.end(); ++it1)
        {
            master_fds.push_back(
                std::make_pair(
                    it1->first.first,
                    it1->first.second));
        }

        FDListener::FDVector::iterator it2;

        ready_fds = FDListener::Wait(master_fds);
        for (it2 = ready_fds.begin(); it2 != ready_fds.end(); ++it2)
        {
            m_fdToFuncs[*it2]();
        }
    }
}

void Reactor::Stop()
{
    m_is_running = false;
}

void Reactor::AddFD(int fd_, Mode mode_, Function func_)
{
    m_fdToFuncs.insert(
        std::make_pair(
            std::make_pair(fd_, static_cast<FDListener::Mode>(mode_)),
        func_));
}

void Reactor::RemoveFD(int fd_, Mode mode_)
{
    m_fdToFuncs.erase(
        std::make_pair(fd_, static_cast<FDListener::Mode>(mode_)));
}


} // namespace ilrd