#include <stdio.h>

#include "stack.hpp"

int main()
{
    Stack s1;

    printf("# Create Stack s1\n");
    printf("IsEmpty: %d\n", s1.IsEmpty());
    printf("Count: %lu\n", s1.Count());

    printf("# After 1 Push\n");
    s1.Push(12);
    printf("IsEmpty: %d\n", s1.IsEmpty());
    printf("Count: %lu\n", s1.Count());
    printf("Top: %d\n", s1.Top());
    printf("# After 2 Push\n");
    s1.Push(15);
    printf("Count: %lu\n", s1.Count());
    printf("Top: %d\n", s1.Top());
    printf("# After 1 Pop\n");
    s1.Pop();
    printf("Count: %lu\n", s1.Count());
    printf("Top: %d\n", s1.Top());
    printf("# After 2 Pop\n");
    s1.Pop();
    printf("IsEmpty: %d\n", s1.IsEmpty());
    printf("Count: %lu\n", s1.Count());
    printf("Top: %d\n", s1.Top());
    s1.Pop();    
}