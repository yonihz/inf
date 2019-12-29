#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "logger.hpp"

void TestDefault();
void TestFile();
void TestOSS();

int main()
{
    TestDefault();
    TestFile();
    TestOSS();
}

void TestDefault()
{
    std::cout << "-----\n" << "cerr test:\n" << "-----" << std::endl;
    Logger log1(Logger::WARNING);
    std::cout << "Default" << std::endl;
    log1.Log(Logger::WARNING, "WARNING msg\n");
    log1.Log(Logger::INFO, "INFO msg\n");
    log1.Log(Logger::DEBUG, "DEBUG msg\n");
    log1.Log(Logger::ERROR, "ERROR msg\n");

    std::cout << std::endl << "OutputSeverity: INFO" << std::endl;
    log1.SetOutputSeverity(Logger::INFO);
    log1.Log(Logger::WARNING, "WARNING msg\n");
    log1.Log(Logger::INFO, "INFO msg\n");
    log1.Log(Logger::DEBUG, "DEBUG msg\n");
    log1.Log(Logger::ERROR, "ERROR msg\n");

    std::cout << std::endl << "OutputSeverity: DEBUG" << std::endl;
    log1.SetOutputSeverity(Logger::DEBUG);
    log1.Log(Logger::WARNING, "WARNING msg\n");
    log1.Log(Logger::INFO, "INFO msg\n");
    log1.Log(Logger::DEBUG, "DEBUG msg\n");
    log1.Log(Logger::ERROR, "ERROR msg\n");

    std::cout << std::endl << "OutputSeverity: WARNING" << std::endl;
    log1.SetOutputSeverity(Logger::WARNING);
    log1.Log(Logger::WARNING, "WARNING msg\n");
    log1.Log(Logger::INFO, "INFO msg\n");
    log1.Log(Logger::DEBUG, "DEBUG msg\n");
    log1.Log(Logger::ERROR, "ERROR msg\n");

    std::cout << std::endl << "OutputSeverity: ERROR" << std::endl;
    log1.SetOutputSeverity(Logger::ERROR);
    log1.Log(Logger::WARNING, "WARNING msg\n");
    log1.Log(Logger::INFO, "INFO msg\n");
    log1.Log(Logger::DEBUG, "DEBUG msg\n");
    log1.Log(Logger::ERROR, "ERROR msg\n");   
}

void TestFile()
{
    std::cout << "-----\n" << "ofstream test:\n" << "-----" << std::endl;
    std::ofstream ofs;
    ofs.open("a.log", std::ofstream::out | std::ofstream::app);

    Logger log1(Logger::WARNING);
    log1.SetOutput(ofs);
    ofs << "Default\n";
    log1.Log(Logger::WARNING, "WARNING msg\n");
    log1.Log(Logger::INFO, "INFO msg\n");
    log1.Log(Logger::DEBUG, "DEBUG msg\n");
    log1.Log(Logger::ERROR, "ERROR msg\n");
    
    ofs << "\nOutputSeverity: INFO\n";
    log1.SetOutputSeverity(Logger::INFO);
    log1.Log(Logger::WARNING, "WARNING msg\n");
    log1.Log(Logger::INFO, "INFO msg\n");
    log1.Log(Logger::DEBUG, "DEBUG msg\n");
    log1.Log(Logger::ERROR, "ERROR msg\n");

    ofs << "\nOutputSeverity: DEBUG\n";
    log1.SetOutputSeverity(Logger::DEBUG);
    log1.Log(Logger::WARNING, "WARNING msg\n");
    log1.Log(Logger::INFO, "INFO msg\n");
    log1.Log(Logger::DEBUG, "DEBUG msg\n");
    log1.Log(Logger::ERROR, "ERROR msg\n");

    ofs << "\nOutputSeverity: WARNING\n";
    log1.SetOutputSeverity(Logger::WARNING);
    log1.Log(Logger::WARNING, "WARNING msg\n");
    log1.Log(Logger::INFO, "INFO msg\n");
    log1.Log(Logger::DEBUG, "DEBUG msg\n");
    log1.Log(Logger::ERROR, "ERROR msg\n");

    ofs << "\nOutputSeverity: ERROR\n";
    log1.SetOutputSeverity(Logger::ERROR);
    log1.Log(Logger::WARNING, "WARNING msg\n");
    log1.Log(Logger::INFO, "INFO msg\n");
    log1.Log(Logger::DEBUG, "DEBUG msg\n");
    log1.Log(Logger::ERROR, "ERROR msg\n");

    ofs.close();
    //std::ifstream ifs("a.log");
    
    //std::cout << ifs.rdbuf();

    // std::string line;
    
    // while(std::getline(ifs, line))
    // {
    //     std::cout << line << '\n';
    // }
}

void TestOSS()
{
    std::ostringstream oss;

    std::cout << "-----\n" << "oss test:\n" << "-----" << std::endl;
    Logger log1(Logger::WARNING);
    log1.SetOutput(oss);
    std::cout << "Default" << std::endl;
    log1.Log(Logger::WARNING, "WARNING msg\n");
    std::cout << "WARNING: " << (oss.str() == "WARNING msg\n") << std::endl;
    oss.str("");
    log1.Log(Logger::INFO, "INFO msg\n");
    std::cout << "INFO: " << (oss.str() == "INFO msg\n") << std::endl;
    oss.str("");
    log1.Log(Logger::DEBUG, "DEBUG msg\n");
    std::cout << "DEBUG: " << (oss.str() == "DEBUG msg\n") << std::endl;
    oss.str("");
    log1.Log(Logger::ERROR, "ERROR msg\n");
    std::cout << "ERROR: " << (oss.str() == "ERROR msg\n") << std::endl;
    oss.str("");
}