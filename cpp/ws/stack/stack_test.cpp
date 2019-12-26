#include <cstdio>

#include "stack.hpp"
#include "string.hpp"

using namespace ilrd;

int main()
{
    Stack<int> s1;
    Stack<class String> s2;

    std::cout << "# Create Stack s1" << std::endl;
    std::cout << "IsEmpty: " << s1.IsEmpty() << std::endl;
    std::cout << "Count: " << s1.Count() << std::endl;

    std::cout << "# After 1 Push" << std::endl;
    s1.Push(12);
    std::cout << "IsEmpty: " << s1.IsEmpty() << std::endl;
    std::cout << "Count: " << s1.Count() << std::endl;
    std::cout << "Top: " << s1.Top() << std::endl;
    std::cout << "# After 2 Push" << std::endl;
    s1.Push(15);
    std::cout << "Count: " << s1.Count() << std::endl;
    std::cout << "Top: " << s1.Top() << std::endl;
    std::cout << "# After 1 Pop" << std::endl;
    s1.Pop();
    std::cout << "Count: " << s1.Count() << std::endl;
    std::cout << "Top: " << s1.Top() << std::endl;
    std::cout << "# After 2 Pop" << std::endl;
    s1.Pop();
    std::cout << "IsEmpty: " << s1.IsEmpty() << std::endl;
    std::cout << "Count: " << s1.Count() << std::endl;
    std::cout << "Top: " << s1.Top() << std::endl;
    s1.Pop();


    std::cout << "# Create Stack s2" << std::endl;
    std::cout << "IsEmpty: " << s2.IsEmpty() << std::endl;
    std::cout << "Count: " << s2.Count();

    std::cout << "# After 1 Push" << std::endl;
    s2.Push("Banana");
    std::cout << "IsEmpty: " << s2.IsEmpty() << std::endl;
    std::cout << "Count: " << s2.Count() << std::endl;
    std::cout << "Top: " << s2.Top() << std::endl;
    std::cout << "# After 2 Push" << std::endl;
    s2.Push("Apple");
    std::cout << "Count: " << s2.Count() << std::endl;
    std::cout << "Top: " << s2.Top() << std::endl;
    std::cout << "# After 1 Pop" << std::endl;
    s2.Pop();
    std::cout << "Count: " << s2.Count() << std::endl;
    std::cout << "Top: " << s2.Top() << std::endl;
    std::cout << "# After 2 Pop" << std::endl;
    s2.Pop();
    std::cout << "IsEmpty: " << s2.IsEmpty() << std::endl;
    std::cout << "Count: " << s2.Count() << std::endl;
    std::cout << "Top: " << s2.Top() << std::endl;
    s2.Pop();


    return 0;
}