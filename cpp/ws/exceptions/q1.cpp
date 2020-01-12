#include <iostream>
// #include <exception>
#include <cstdlib>

using namespace std;

void myunexpected () {
  std::cerr << "unexpected called\n";
  throw 0;     // throws int (in exception-specification)
}

struct BadDog: public runtime_error
{
    BadDog(const string& s_ = "This is a bad dog")
        : runtime_error(s_)
        {
            cout << "BadDog Ctor" << endl;
        }
};

struct A
{
    A()
    {
        cout << "A Ctor" << endl;
    }
    ~A()
    {
        cout << "A Dtor" << endl;
    }
};

void Fifi() throw(int)
{
    throw BadDog("bad pup");
    cerr << "Fifi() after throw" << endl;
}

void Foo() 
{
    A a;
    Fifi();
    cerr << "Foo() after Fifi()" << endl;
}

void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}

int main()
{
    std::set_unexpected (myunexpected);

    try
    {
        Bar();
    }
    catch(bad_alloc)
    {
        cerr << "Out of memory! exiting."; exit(2);
    }
    catch(BadDog &b)
    {
        cerr << "Bad dog exception: " << b.what();
        exit(3);
    }
    catch( exception& r )
    {
        cerr << "unknown exception: " << r.what();
        exit(4);
    }
    catch (...)
    {
        cout << "default exception";
    }

    return 0;
}

// without set_unexpected

// (gdb) bt     
// #0  __GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:51
// #1  0x00007f410de23801 in __GI_abort () at abort.c:79
// #2  0x00007f410e478957 in ?? () from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
// #3  0x00007f410e47eab6 in ?? () from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
// #4  0x00007f410e47eaf1 in std::terminate() () from /usr/lib/x86_64-linux-gnu/lib
// stdc++.so.6
// #5  0x00007f410e47eb06 in ?? () from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
// #6  0x00007f410e47e7e2 in __cxa_call_unexpected () from /usr/lib/x86_64-linux-gn
// u/libstdc++.so.6
// #7  0x000056396b1d943a in Fifi () at q1.cpp:33
// #8  0x000056396b1d9463 in Foo () at q1.cpp:42
// #9  0x000056396b1d94d8 in Bar () at q1.cpp:48
// #10 0x000056396b1d9520 in main () at q1.cpp:58
