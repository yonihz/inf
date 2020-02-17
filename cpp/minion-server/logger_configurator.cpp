#include "boost/lexical_cast.hpp" 
using boost::lexical_cast;

#include "logger_configurator.hpp"
#include "logger.hpp"
#include "singleton.hpp"

namespace ilrd
{

LoggerConfigurator::LoggerConfigurator()
    : m_ofs() {}

LoggerConfigurator::~LoggerConfigurator()
{
    m_ofs->close();
}
    
void LoggerConfigurator::operator()(void)
{
    std::ifstream configuration_file("./addons/logger.ini");
    std::string output_filename;
    std::getline(configuration_file, output_filename);
    configuration_file.close();

    Logger &logger = *(Singleton<Logger>::Instance());
    boost::shared_ptr<std::ofstream> ofs(new std::ofstream(output_filename));
    m_ofs = ofs;

    logger.SetOutput(*m_ofs);   
}


} // namespace ilrd