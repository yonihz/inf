#ifndef _ILRD_RD734_SP_HPP_
#define _ILRD_RD734_SP_HPP_

#include <iostream>
#include <cstddef>

namespace ilrd
{

template <class T>
class SharedPtr
{
public:
    explicit SharedPtr(T* t_);
    SharedPtr(const SharedPtr<T>& other_);

    template<class S>
    friend class SharedPtr;

    template<class S>
    SharedPtr(const SharedPtr<S>& other_);

    SharedPtr& operator=(const SharedPtr<T>& other_);
    ~SharedPtr();
    T& operator*() const;
    T* operator->() const;
    size_t UseCount() const;

private:
    void CleanUp();

    T* m_ptr;
    size_t* m_counter;
};

template <class T>
SharedPtr<T>::SharedPtr(T* t_)
    : m_ptr(t_), m_counter(new size_t(1))
{
    // std::cout << "Ctor " << m_ptr << std::endl;
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other_)
    : m_ptr(other_.m_ptr), m_counter(other_.m_counter)
{
    ++(*m_counter);
    // std::cout << "CCtor "  << m_ptr << std::endl;
}

template <class T>
template <class S>
SharedPtr<T>::SharedPtr(const SharedPtr<S>& other_)
    : m_ptr(other_.m_ptr), m_counter(other_.m_counter)
{
    ++(*m_counter);
    // std::cout << "Conversion Ctor " << m_ptr << std::endl;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other_)
{
    if (m_ptr == other_.m_ptr)
    {
        // std::cout << "operator= does nothing" << std::endl;
        return *this;
    }

    --(*m_counter);

    if (0 == *m_counter)
    {
        CleanUp();
    }

    m_ptr = other_.m_ptr;
    m_counter = other_.m_counter;
    ++(*m_counter);
    return *this;
}

template <class T>
SharedPtr<T>::~SharedPtr()
{
    --(*m_counter);

    if (0 == *m_counter)
    {
        CleanUp();
        
    }
}

template <class T>
T& SharedPtr<T>::operator*() const
{
    return (*m_ptr);
}

template <class T>
T* SharedPtr<T>::operator->() const
{
    return m_ptr;
}

template <class T>
size_t SharedPtr<T>::UseCount() const
{
    return *m_counter;
}

template <class T>
void SharedPtr<T>::CleanUp()
{
    // std::cout << "CleanUp() " << m_ptr << std::endl;
    delete m_counter;
    delete m_ptr;
    m_ptr = NULL;
}

} // namespace ilrd

#endif // _ILRD_RD734_SP_HPP_