#include <iostream>
#include <mutex>

#include "scope_guard.hpp"

std::mutex mutex_lock;

int main () 
{
    {
        std::cout << "start of scope\n";
        ilrd::ScopeGuard<std::mutex, &std::mutex::lock, &std::mutex::unlock> sg(mutex_lock);
        std::cout << "end of scope\n";
    }
}