#ifndef _ILRD_RD734_PLUGIN_LOADER_HPP_
#define _ILRD_RD734_PLUGIN_LOADER_HPP_

#include <string>
#include <set>

#include "command.hpp"

namespace ilrd
{

class PluginLoader
{
public:
    PluginLoader(CommandManager *cmd_manager_);
    
    void operator()(std::string &name);

private:
    CommandManager *m_cmd_manager;
    std::set<std::string> m_shared_objs; 
};

} // namespace ilrd

#endif // _ILRD_RD734_PLUGIN_LOADER_HPP_