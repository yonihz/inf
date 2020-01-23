#ifndef _ILRD_RD734_SERIALIZER_HPP_
#define _ILRD_RD734_SERIALIZER_HPP_

#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <boost/core/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

// map<std::string, std::string> ToMap(T&);
namespace ilrd
{

template <typename T>
class Serializer : private boost::noncopyable
{
    typedef boost::shared_ptr<T> (*Creator)(std::map<std::string, std::string>&);

public:
    Serializer(std::iostream& ios_);
    ~Serializer();

    template <typename D>
    void AddType(Creator creator_);  

    void Serialize(std::vector<T*>& instances_);
    std::vector<boost::shared_ptr<T> > Deserialize(); //throws: type_not_found, bad_alloc

private:
    std::map<std::string, Creator> m_types;
    std::iostream m_ios;
};

template <typename T>
Serializer<T>::Serializer(std::iostream& ios_)
    : m_types(), m_ios(ios_)
{
}

template <typename T>
Serializer<T>::~Serializer()
{
}

template <typename T>
template <typename D>
void Serializer<T>::AddType(Creator creator_)
{
    m_types.insert(creator_);
}  

template <typename T>
void Serializer<T>::Serialize(std::vector<T*>& instances_)
{
    instances_.insert();
}

template <typename T>
std::vector<boost::shared_ptr<T> > Serializer<T>::Deserialize()
{

}

} // namespace ilrd

#endif // _ILRD_RD734_SERIALIZER_HPP_
