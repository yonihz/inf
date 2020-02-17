#include <dlfcn.h>

#include "boost/lexical_cast.hpp" 
using boost::lexical_cast;

#include "plugin_loader.hpp"
#include "logger.hpp"
#include "singleton.hpp"

namespace ilrd
{

PluginLoader::PluginLoader(CommandManager *cmd_manager_)
    : m_cmd_manager(cmd_manager_), m_shared_objs() {}

void PluginLoader::operator()(std::string &name)
{
    Logger &logger = *(Singleton<Logger>::Instance());

    // if (m_shared_objs.find(name) != m_shared_objs.end())
    // {
    //     logger.Log(Logger::ERROR, 
    //         "plugin error: already exists: " + 
    //         lexical_cast<std::string>(event->wd) + "\n");
    // }
    // else
    // {
    //     m_shared_objs.insert(name);
    //     LoadLib(name);
    // }

    m_shared_objs.insert(name);
    
    void *handle;
    char *error;
    boost::shared_ptr<Command> (*Creator)();
    char (*GetKey)(void);
    std::string dir("./add_ons/");
    std::string path = dir + name;

    handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle)
    {
        logger.Log(Logger::ERROR, "dlopen: " + std::string(dlerror()) + "\n");
        return;
    }

    Creator = (boost::shared_ptr<Command>(*)()) dlsym(handle, "Creator");
    if ((error = dlerror()) != NULL)
    {
        logger.Log(Logger::ERROR, "dlsym: " + std::string(error) + "\n");
        return;
    }

    GetKey = (char(*)(void)) dlsym(handle, "GetKey");
    if ((error = dlerror()) != NULL) 
    {
        logger.Log(Logger::ERROR, "dlsym: " + std::string(error) + "\n");
        return;
    }

    m_cmd_manager->AddCommand((int)(*GetKey)(), Creator);
}

} // namespace ilrd