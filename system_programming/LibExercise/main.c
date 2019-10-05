#include <stdio.h>
#include <dlfcn.h>

extern void Foo();
extern void Bar1();

int main()
{
    void *handle;
    void (*ptr_Bar2)();
    char *error;

    handle = dlopen ("/usr/lib/x86_64-linux-gnu/libso2.so", RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        return (0);
    }

    ptr_Bar2 = dlsym(handle, "Bar2");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        return (0);
    }

    (*ptr_Bar2)();
    dlclose(handle);

    Foo();
    Bar1(); /* implicit linking */

    /* Bar2(); explicit linking (DL) */

    return (0);
}

/*
Create object files:
gcc -c main.c
gcc -c a.c
gcc -c a1.c
gcc -c a2.c
gcc -c -fPIC so1.c
gcc -c -fPIC so2.c

Create static library:
ar rcs libar.a a.o a1.o a2.o

Link with static lib:
gcc main.o -L. -lar -o prog1

Create shared library:
sudo gcc -shared so1.o -o /usr/lib/x86_64-linux-gnu/libso1.so
sudo gcc -shared so2.o -o /usr/lib/x86_64-linux-gnu/libso2.so

Link dynamically with the shared library:
gcc main.o -L. -lar -L/usr/lib/x86_64-linux-gnu/ -lso1 -o prog

Link dynamically with the shared library and ldl flag for dl functions:
gcc main.o -L. -lar -L/usr/lib/x86_64-linux-gnu/ -lso1 -ldl -o prog
*/

