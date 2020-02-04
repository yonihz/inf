#ifndef ILRD_RD734_SINGLETON_HPP
#define ILRD_RD734_SINGLETON_HPP

#include <boost/interprocess/sync/interprocess_mutex.hpp>

namespace ilrd
{

template<typename T>
class Singleton
{
public:
    static T* Instance();

private:
    static T* m_pInstance;
    static boost::interprocess::interprocess_mutex m_mutex;

    Singleton();
};

template<typename T>
T* Singleton<T>::m_pInstance = NULL;

template<typename T>
boost::interprocess::interprocess_mutex Singleton<T>::m_mutex;

template<typename T>
T* Singleton<T>::Instance()
{
    if (m_pInstance == NULL)
    {
        m_mutex.lock();
        if (m_pInstance == NULL)
        {
            m_pInstance = new T;
        }
        m_mutex.unlock();
    }

    return m_pInstance;
}

}

#endif // ILRD_RD734_SINGLETON_HPP