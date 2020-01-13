#include <iostream>

void Bar(int* arr) {}
void Fishi() {}
void Dodo() {}

void Foo(bool goKaboomEarly)
{
    int *arr1;
    try
    {
        arr1 = new int[10];
    }
    catch(std::bad_alloc)
    {
        std::cerr << "Out of memory! exiting."; exit(2);
    }

    if (goKaboomEarly)
    {
        Bar(arr1);
    }

    int *arr2;
    try
    {
        arr2 = new int[100];
    }
    catch(std::bad_alloc)
    {
        std::cerr << "Out of memory! exiting."; exit(2);
    }
    
    Fishi();
    Bar(arr2);
    Dodo();

    delete[] arr2;
    delete[] arr1;
}