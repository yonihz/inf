#ifndef _ILRD_RD734_SERIALIZER_HPP_
#define _ILRD_RD734_SERIALIZER_HPP_

#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <boost/core/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <algorithm>

// user must have a function that take an instance of a class and make
// map<string, string> of it.
// map<std::string, std::string> ToMap(T&);

namespace ilrd
{

template <typename T>
class Serializer : private boost::noncopyable
{
    typedef boost::shared_ptr<T> (*Creator)(std::map<std::string, std::string>);

public:
    Serializer(std::ostream& ios_);
    ~Serializer();

    template <typename D>
    void AddType(Creator creator_);  

    void Serialize(std::vector<T*>& instances_);

    //throws: type_not_found, bad_alloc
    std::vector<boost::shared_ptr<T> > Deserialize(); 

private:
    std::map<std::string, Creator> m_types;
    std::ostream &m_ios;

    struct MapInstance;
    MapInstance m_map_instance;
};

template <typename T>
Serializer<T>::Serializer(std::ostream& ios_)
    : m_types(), m_ios(ios_), m_map_instance(ios_)
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
    m_types.insert(std::pair<std::string,std::string>(
        typeid(T).name,
        creator_));
}  

template <typename T>
void Serializer<T>::Serialize(std::vector<T*>& instances_)
{
    m_ios << "START_SERIAL" << ":";
    std::for_each(instances_.begin(), instances_.end(), m_map_instance);
    m_ios << "END_SERIAL";
}

template <typename T>
std::vector<boost::shared_ptr<T> > Serializer<T>::Deserialize()
{
    
}

template <typename T>
struct Serializer<T>::MapInstance
{
    MapInstance(std::ostream& ios_) : m_ios(ios_), m_serialize_instance(ios_) { }

    struct SerializeInstance;
    
    void operator()(T* instance)
    {
        m_ios << typeid(T).name() << ":";
        std::map<std::string, std::string> instance_m = instance->ToMap();
        std::for_each(instance_m.begin(), instance_m.end(), m_serialize_instance);
    }

    std::ostream &m_ios;
    SerializeInstance m_serialize_instance;
};

template <typename T>
struct Serializer<T>::MapInstance::SerializeInstance
{
    SerializeInstance(std::ostream& ios_) : m_ios(ios_) { }

    void operator()(std::pair<std::string, std::string> pair)
    {
        m_ios << pair.first;
        m_ios << pair.second;
        m_ios << ":";
    }

    std::ostream &m_ios;
};

} // namespace ilrd

#endif // _ILRD_RD734_SERIALIZER_HPP_
