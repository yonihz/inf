#ifndef ILRD_OL734_STACK_HPP
#define ILRD_OL734_STACK_HPP

#include <stdlib.h>

typedef int DataType;

struct Stack
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
    struct Node
    {
        explicit Node();
        explicit Node(DataType data, const Node *next);

        DataType GetData() const;
        bool HasNext() const;
        const Node &GetNext() const;

        const DataType m_data;
        const Node* m_next;
    };

    Node m_dummy;
};

#endif