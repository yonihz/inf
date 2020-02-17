#include "command.hpp"

namespace ilrd
{

CommandManager::CommandManager(Reactor *reactor_)
    : m_reactor(reactor_), m_factory() {}

void CommandManager::RunCommand(char c_, char *buffer_)
{
    (*m_factory.Create(c_))(buffer_);
}

void CommandManager::AddCommand(char c_, boost::shared_ptr<Command>(*creator_)(void))
{
    m_factory.Add((int)c_, creator_);
}

} //namespace ilrd