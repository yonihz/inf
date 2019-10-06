#include <stdio.h>
#include <dlfcn.h>

extern void Foo();
extern void Bar1();

int main()
{
    void *handle;
    void (*ptr_Bar2)();
    char *error;

    Foo();
    Bar1(); /* Bar1() with implicit linking */

    /* Bar2() with explicit linking (DL) */

    handle = dlopen ("./libso2.so", RTLD_LAZY);
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

    return (0);
}