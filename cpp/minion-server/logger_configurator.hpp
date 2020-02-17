#ifndef _ILRD_RD734_LOGGER_CONFIGURATOR_HPP_
#define _ILRD_RD734_LOGGER_CONFIGURATOR_HPP_

#include <fstream>

#include <boost/shared_ptr.hpp>

namespace ilrd
{

class LoggerConfigurator
{
public:
    LoggerConfigurator();
    
    void operator()(void);

private:
    boost::shared_ptr<std::ofstream> m_ofs;    
};

} // namespace ilrd

#endif // _ILRD_RD734_LOGGER_CONFIGURATOR_HPP_