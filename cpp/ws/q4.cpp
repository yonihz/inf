/*
g++ -ansi -pedantic-errors -Wall -Wextra -c -fPIC q4so.cpp
g++ -ansi -pedantic-errors -Wall -Wextra -c -fPIC q4.cpp
g++ -shared q4so.o -o libq4so.so
g++ q4.o -Wl,-rpath,. -ldl -o q4.out
*/

#include <stdio.h>
#include <dlfcn.h>

void Foo()
{
    printf("void arg\n");
}

/*
void Foo(int i)
{
    (void)(i);
    printf("int arg\n");
}

void Foo(char c)
{
    (void)(c);
    printf("char arg\n");
}
*/

int main()
{
    void *handle;
    void (*ptr_Bar1)();
    char *error;
    int a1 = 1;
    char c1 = 48;

/*
    Foo();
    Foo(a1);
    Foo(c1);
*/

    handle = dlopen ("./libq4so.so", RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        return (0);
    }

    *(void **) (&ptr_Bar1) = dlsym(handle, "Bar1");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        return (0);
    }

    (*ptr_Bar1)();
    dlclose(handle);

    return (0);
}