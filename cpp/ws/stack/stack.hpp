#ifndef ILRD_OL734_STACK_HPP
#define ILRD_OL734_STACK_HPP

#include <cstdlib>
#include <detail.hpp>

template <class DataType>
class Stack
{
public:
    explicit Stack();
    ~Stack();

    void Push(DataType data);
    void Pop();
    DataType Top() const;
    size_t Count() const;
    bool IsEmpty() const;

private:
    class Node
    {
        public:
            explicit Node(DataType data = DataType(), const Node *next = Deadbeef<Node>());

            DataType GetData() const;
            bool HasNext() const;
            const Node &GetNext() const;

            const DataType m_data;
            const Node* m_next;
    };

    Node m_dummy;
};

template <class DataType>
Stack<DataType>::Stack() {}

template <class DataType>
Stack<DataType>::~Stack()
{
    while (!IsEmpty())
    {
        Pop();
    }
}

template <class DataType>
void Stack<DataType>::Push(DataType data)
{
    m_dummy.m_next = new Node(data, m_dummy.m_next);
}

template <class DataType>
void Stack<DataType>::Pop()
{
    if (IsEmpty())
    {
        return;
    }

    const Node *to_remove = m_dummy.m_next;
    m_dummy.m_next = m_dummy.m_next->m_next; 
    
    delete to_remove;
}

template <class DataType>
DataType Stack<DataType>::Top() const
{
    if (IsEmpty())
    {
        return DataType();
    }
    
    return m_dummy.m_next->GetData();
}

template <class DataType>
size_t Stack<DataType>::Count() const
{
    size_t size = 0;
    const Node *curr = &m_dummy;

    while (curr->HasNext())
    {
        ++size;
        curr = &curr->GetNext();
    }

    return size;
}

template <class DataType>
bool Stack<DataType>::IsEmpty() const
{
    return !(m_dummy.HasNext());
}

template <class DataType>
Stack<DataType>::Node::Node(DataType data, const Node *next)
    : m_data(data), m_next(next)
{

}

template <class DataType>
DataType Stack<DataType>::Node::GetData() const
{
    return m_data;
}

template <class DataType>
bool Stack<DataType>::Node::HasNext() const
{
    return (this->m_next != Deadbeef<Node>());
}

template <class DataType>
const typename Stack<DataType>::Node &Stack<DataType>::Node::GetNext() const
{
    return *m_next;
}

#endif