#include "stack.hpp"

Stack::Stack()
    : m_dummy(0, NULL)
{

}

Stack::~Stack()
{

}

void Stack::Push(DataType data)
{
    m_dummy.m_next = new Node(data, m_dummy.m_next);
}

void Stack::Pop()
{
    if (IsEmpty())
    {
        return;
    }

    const Node *to_remove = m_dummy.m_next;
    m_dummy.m_next = m_dummy.m_next->m_next; 
    
    delete to_remove;
}

DataType Stack::Top() const
{
    if (IsEmpty())
    {
        return 0;
    }
    
    return m_dummy.m_next->GetData();
}

size_t Stack::Count() const
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

bool Stack::IsEmpty() const
{
    return !(m_dummy.HasNext());
}

Stack::Node::Node()
    : m_data(0), m_next(NULL)
{

}

Stack::Node::Node(DataType data, const Node *next)
    : m_data(data), m_next(next)
{

}

DataType Stack::Node::GetData() const
{
    return m_data;
}

bool Stack::Node::HasNext() const
{
    return (this->m_next != NULL);
}

const Stack::Node &Stack::Node::GetNext() const
{
    return *m_next;
}
