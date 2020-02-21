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

void PluginLoader::operator()(std::string name)
{
    Logger &logger = *(Singleton<Logger>::Instance());

    if (name == "logger.ini")
    {
        return;
    }

    //TODO: check if name already exists
    //TODO: check name ends with .so

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

    m_shared_objs.insert(name);
    m_cmd_manager->AddCommand((int)(*GetKey)(), Creator);
}

void PluginLoader::OnDispatcherDeath(void)
{
}

} // namespace ilrd