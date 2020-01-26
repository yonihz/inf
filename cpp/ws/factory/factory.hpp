#ifndef _ILRD_OL734_FACTORY_HPP_
#define _ILRD_OL734_FACTORY_HPP_

#include <map>

namespace ilrd
{

template <typename Obj_Handle, typename Key, typename Data, typename Create_Func = Obj_Handle(*)(Data)>
class Factory
{

public:
    void Add(Key key_, Create_Func creator_);  
    Obj_Handle Create(Key key_, Data data_);

private:
    std::map<Key, Create_Func> m_map;
};

template <typename Obj_Handle, typename Key, typename Data, typename Create_Func>
void Factory<Obj_Handle, Key, Data, Create_Func>::Add(Key key_, Create_Func creator_)
{
    m_map.insert(std::pair<Key, Create_Func>(key_, creator_));
}

template <typename Obj_Handle, typename Key, typename Data, typename Create_Func>
Obj_Handle Factory<Obj_Handle, Key, Data, Create_Func>::Create(Key key_, Data data_)
{
    return m_map[key_](data_);
}

} // namespace ilrd

#endif // _ILRD_OL734_FACTORY_HPP_