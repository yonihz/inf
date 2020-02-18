#ifndef _ILRD_RD734_SERVER_CALLBACKS_HPP_
#define _ILRD_RD734_SERVER_CALLBACKS_HPP_

#include <string>

#include "dispatcher.hpp"
#include "logger_configurator.hpp"
#include "plugin_loader.hpp"

namespace ilrd
{

class LoggerConfiguratorCallback : public Callback<LoggerConfigurator, std::string>
{
public:
    LoggerConfiguratorCallback(LoggerConfigurator& logger_configurator, void (LoggerConfigurator::*notify_)(std::string), void (LoggerConfigurator::*notifyDeath_)(void));
    void Notify(std::string name_);
    void NotifyDeath();    
};

class PluginLoaderCallback : public Callback<PluginLoader, std::string>
{
public:
    PluginLoaderCallback(PluginLoader& logger_configurator, void (PluginLoader::*notify_)(std::string), void (PluginLoader::*notifyDeath_)(void));
    void Notify(std::string name_);
    void NotifyDeath();    
};

} // namespace ilrd

#endif // _ILRD_RD734_SERVER_CALLBACKS_HPP_