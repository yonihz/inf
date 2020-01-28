#ifndef _ILRD_RD734_SERIALIZER_HPP_
#define _ILRD_RD734_SERIALIZER_HPP_

#include <memory>
#include <iostream>                             // op<<, op>>
#include <vector>                               // std::vector
#include <map>                                  // std::map
#include <string>                               // std::string
#include <boost/core/noncopyable.hpp>           // boost noncopyable
#include <boost/shared_ptr.hpp>                 // boost shared ptr
#include <algorithm>                            // for_each
#include <boost/property_tree/ptree.hpp>        // boost ptree
#include <boost/property_tree/json_parser.hpp>  // write_json, read_json
#include <boost/foreach.hpp>                    // BOOST_FOREACH

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

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
    Serializer(std::iostream& ios_);
    ~Serializer();

    template <typename D>
    void AddType(Creator creator_);  

    void Serialize(std::vector<T*>& instances_);

    //throws: type_not_found, bad_alloc
    std::vector<boost::shared_ptr<T> > Deserialize(); 

private:
    std::map<std::string, Creator> m_types;
    std::iostream &m_ios;

    struct MapInstance;
    MapInstance m_map_instance;
};

template <typename T>
Serializer<T>::Serializer(std::iostream& ios_)
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
    m_types.insert(std::pair<std::string, Creator>(typeid(D*).name(), creator_));
}  

template <typename T>
void Serializer<T>::Serialize(std::vector<T*>& instances_)
{
    std::for_each(instances_.begin(), instances_.end(), m_map_instance);

    write_json(m_ios, *m_map_instance.GetPT());
}

template <typename T>
std::vector<boost::shared_ptr<T> > Serializer<T>::Deserialize()
{
    std::vector< boost::shared_ptr<T> > instances;
    ptree pt;
    read_json(m_ios, pt);
    BOOST_FOREACH(boost::property_tree::ptree::value_type& iter_instance, pt)
    {
        std::map<std::string, std::string> type_map;
        BOOST_FOREACH(boost::property_tree::ptree::value_type& iter_property, iter_instance.second)
        {
            type_map.insert(std::pair<std::string,std::string>(iter_property.first, iter_property.second.data()));
        }
        instances.push_back(m_types[type_map["type"]](type_map));
    }

    return instances;
}

template <typename T>
struct Serializer<T>::MapInstance
{
    MapInstance(std::iostream& ios_) 
        : m_ios(ios_), m_child(new ptree), m_pt(new ptree), m_serialize_instance(ios_, m_child) {}

    ~MapInstance()
    {
        // m_pt->clear();
        // m_child->clear();
        // delete m_pt;
        // delete m_child;
    }

    struct SerializeInstance;
    
    ptree *GetPT() { return m_pt; }

    void operator()(T* instance)
    {
        std::map<std::string, std::string> instance_m = instance->ToMap();
        std::for_each(instance_m.rbegin(), instance_m.rend(), m_serialize_instance);
        m_pt->add_child("type", *m_child);

        m_child->clear();
    }

    std::iostream &m_ios;
    ptree *m_child;
    ptree *m_pt;
    SerializeInstance m_serialize_instance;
};

template <typename T>
struct Serializer<T>::MapInstance::SerializeInstance
{
    SerializeInstance(std::iostream& ios_, ptree *child_)
        : m_ios(ios_), m_child(child_) {}

    void operator()(std::pair<std::string, std::string> pair)
    {
        (*m_child).put(pair.first, pair.second);
    }

    std::iostream &m_ios;
    ptree *m_child;
};

} // namespace ilrd

#endif // _ILRD_RD734_SERIALIZER_HPP_
