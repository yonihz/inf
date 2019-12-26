#include "histo.hpp"

namespace ilrd
{

void Histo()
{
    std::string s1 = "";
    std::queue<std::string> q1;
    std::multiset<std::string> m1;
    size_t count = 0;

    std::cout << "Enter text (. to end program):\n" << "-----\n";
    getline(std::cin, s1);

    while (s1 != ".")
    {
        q1.push(s1);
        m1.insert(s1);
        getline(std::cin, s1);
    }

    std::cout << "End text\n" << "-----\n";
    
    while (!q1.empty())
    {
        count = m1.count(q1.front());
        if (count > 1)
        {
            std::cout << count  << " X " << q1.front() << std::endl;
        }
        else if (count == 1)
        {
            std::cout << q1.front() << std::endl;
        }

        m1.erase(q1.front());
        q1.pop();
    }
}

}