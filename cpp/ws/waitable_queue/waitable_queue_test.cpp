#include <iostream>
#include <queue>
#include <vector>
#include <boost/thread/thread.hpp>

#include "waitable_queue.hpp"

using namespace ilrd;

void writer();
void reader();

WaitableQueue< std::queue<int> > q1;
int g_i = 0;

int main()
{
    const size_t nwriters = 10;
    const size_t nreaders = 10;
    
    boost::thread writers_arr[nwriters];
    boost::thread readers_arr[nreaders];

    for (size_t i = 0; i < nwriters; ++i)
    {
        writers_arr[i] = boost::thread(&writer);
    }

    for (size_t i = 0; i < nreaders; ++i)
    {
        readers_arr[i] = boost::thread(&reader);
    }

    for (size_t i = 0; i < nwriters; ++i)
    {
        writers_arr[i].join();
    }

    for (size_t i = 0; i < nreaders; ++i)
    {
        readers_arr[i].join();
    }

    return 0;
}

void writer()
{
    q1.Push(++g_i);
}

void reader()
{
    int i;
    q1.Pop(i, 1);
}