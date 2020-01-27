#ifndef _ILRD_OL734_FACTORY_HPP_
#define _ILRD_OL734_FACTORY_HPP_

#include <map>

namespace ilrd
{

class InvalidKey;

template <typename Obj_Handle, typename Key, typename Data, typename Create_Func = Obj_Handle(*)(Data)>
class Factory
{

public:
    void Add(const Key key_, Create_Func creator_);  // does nothing if key exists
    Obj_Handle Create(Key key_, Data data_) const;

private:
    typedef std::map<Key, Create_Func> factory_map_t;
    factory_map_t m_map;
};

//  specialization for Data = void
template <typename Obj_Handle, typename Key>
class Factory <Obj_Handle, Key, void, Obj_Handle(*)(void)>
{

public:
    void Add(const Key key_, Obj_Handle(*)(void));  
    Obj_Handle Create(Key key_) const;

private:
    typedef std::map<Key, Obj_Handle(*)(void)> factory_map_t;
    factory_map_t m_map;
};

template <typename Obj_Handle, typename Key, typename Data, typename Create_Func>
void Factory<Obj_Handle, Key, Data, Create_Func>::Add(const Key key_, Create_Func creator_)
{
    m_map.insert(std::pair<Key, Create_Func>(key_, creator_));
}

//  specialization for Data = void
template <typename Obj_Handle, typename Key>
void Factory<Obj_Handle, Key, void, Obj_Handle(*)(void)>::Add(const Key key_, Obj_Handle(*creator_)(void))
{
    m_map.insert(std::pair<Key, Obj_Handle(*)(void)>(key_, creator_));
}

template <typename Obj_Handle, typename Key, typename Data, typename Create_Func>
Obj_Handle Factory<Obj_Handle, Key, Data, Create_Func>::Create(Key key_, Data data_) const
{
    typename factory_map_t::const_iterator iter = m_map.find(key_);
    if (iter == m_map.end())
    {
        throw InvalidKey();
    }

    return iter->second(data_);
}

//  specialization for Data = void
template <typename Obj_Handle, typename Key>
Obj_Handle Factory<Obj_Handle, Key, void, Obj_Handle(*)(void)>::Create(Key key_) const
{
    typename factory_map_t::const_iterator iter = m_map.find(key_);
    if (iter == m_map.end())
    {
        throw InvalidKey();
    }

    return iter->second();
}

class InvalidKey : public std::runtime_error
{
public:
    InvalidKey(const std::string& s_ = "Invalid key for Creator function")
        : runtime_error(s_) { }
};

} // namespace ilrd

#endif // _ILRD_OL734_FACTORY_HPP_