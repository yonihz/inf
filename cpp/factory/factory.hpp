#ifndef _ILRD_OL734_FACTORY_HPP_
#define _ILRD_OL734_FACTORY_HPP_

#include <stdexcept>
#include <map>

namespace ilrd
{

class InvalidKey;

template <typename Obj_Handle, typename Key, typename Data, typename Create_Func = Obj_Handle(*)(Data)>
class Factory
{

public:
    void Add(const Key key_, Create_Func creator_);  // overrides if key exists
    Obj_Handle Create(Key key_, Data data_) const; // may throw InvalidKey() exception if key is invalid

private:
    typedef std::map<Key, Create_Func> factory_map_t;
    factory_map_t m_map;
};

template <typename Obj_Handle, typename Key, typename Data, typename Create_Func>
void Factory<Obj_Handle, Key, Data, Create_Func>::Add(const Key key_, Create_Func creator_)
{
    m_map[key_] = creator_;
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

/******************************************************************************/
/****** specialization for Data = void ****************************************/
/******************************************************************************/

template <typename Obj_Handle, typename Key, typename Create_Func>
class Factory <Obj_Handle, Key, void, Create_Func>
{

public:
    void Add(const Key key_, Create_Func creator_);  
    Obj_Handle Create(Key key_) const;

private:
    typedef std::map<Key, Create_Func> factory_map_t;
    factory_map_t m_map;
};

template <typename Obj_Handle, typename Key, typename Create_Func>
void Factory<Obj_Handle, Key, void, Create_Func>::Add(const Key key_, Create_Func creator_)
{
    m_map[key_] = creator_;
}

template <typename Obj_Handle, typename Key, typename Create_Func>
Obj_Handle Factory<Obj_Handle, Key, void, Create_Func>::Create(Key key_) const
{
    typename factory_map_t::const_iterator iter = m_map.find(key_);
    if (iter == m_map.end())
    {
        throw InvalidKey();
    }

    return iter->second();
}

/******************************************************************************/
/****** InvalidKey ************************************************************/
/******************************************************************************/

class InvalidKey : public std::runtime_error
{
public:
    InvalidKey(const std::string& s_ = "Invalid key for Creator function")
        : runtime_error(s_) { }
};

} // namespace ilrd

#endif // _ILRD_OL734_FACTORY_HPP_