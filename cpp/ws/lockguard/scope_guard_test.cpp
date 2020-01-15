#include <iostream>
#include <fstream>
#include <mutex>

#include "scope_guard.hpp"

class File
{
public:
    File(std::string filename_) : m_filename(filename_) { }
    
    ~File() { };

    void Acquire()
    {
        std::cout << "Acquire\n";
        m_file.open(m_filename.c_str(), std::ofstream::out | std::ofstream::app);
        
    }

    void Release()
    {
        std::cout << "Release\n";
        m_file.close();
    }

    std::fstream& GetFile()
    {
        return m_file;
    }

private:
    std::fstream m_file;
    std::string m_filename;
};

int main () 
{
    File file1("my_file.log");

    {
        std::cout << "start of scope\n";
        ilrd::ScopeGuard<File, &File::Acquire, &File::Release> sg(file1);

        file1.GetFile() << "Hello\n";
        file1.GetFile() << "la la la\n";
        std::cout << "end of scope\n";
    }
}