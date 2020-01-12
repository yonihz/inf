#include <iostream>
#include <exception>

struct ThrowAtDefCtor
{
    ThrowAtDefCtor()
    {
        std::cerr << "throwAtDefCtor" << std::endl;
    }

    ThrowAtDefCtor(int) { std::cerr << "ThrowAtDefCtor Ctor (int)" << std::endl;}
    ~ThrowAtDefCtor() { std::cerr << "ThrowAtDefCtor Dtor" << std::endl;}
};

struct NoThrow
{
    NoThrow() {std::cerr << "NoThrow Ctor" << std::endl; }
    ~NoThrow() {std::cerr << "NoThrow Dtor" << std::endl; }
};

class X
{
public:
    X() : m_tdc(2) { std::cerr << "X Ctor" << std::endl; }
    ~X() { std::cerr << "X Dtor" << std::endl; }

private:
    NoThrow m_nt;
    ThrowAtDefCtor m_tdc;
};

class Y
{
public:
    Y() { std::cerr << "Y Ctor" << std::endl; }
    ~Y() { std::cerr << "Y Dtor" << std::endl; }

private:
    ThrowAtDefCtor m_dtc;
    NoThrow m_nt;
};

class Z
{
public:
    Z() { std::cerr << "Z Ctor" << std::endl; }
    ~Z() { std::cerr << "Z Dtor" << std::endl; }

private:
    NoThrow m_nt;
    ThrowAtDefCtor m_dtc;
};

class YPtrs
{
public:
    YPtrs()
    : m_dtc(new ThrowAtDefCtor)
    , m_nt(new NoThrow)
    {
        std::cerr << "YPtrs Ctor" << std::endl;
    }
    ~YPtrs()
    {
        std::cerr << "YPtrs Dtor" << std::endl;
        delete m_nt;
        delete m_dtc;
    }
private:
    ThrowAtDefCtor *m_dtc;
    NoThrow *m_nt;
};

class ZPtrs
{
public:
    ZPtrs()
    {
        std::cerr << "ZPtrs Ctor" << std::endl;
        m_nt = new NoThrow;
        m_dtc = new ThrowAtDefCtor;
    }
    ~ZPtrs()
    {
        std::cerr << "ZPtrs Dtor" << std::endl;
        delete m_dtc;
        delete m_nt;
    }
private:
    NoThrow *m_nt;
    ThrowAtDefCtor *m_dtc;
};


int main()
{
    try
    {
        X var1;
        //Y var;
        //Z var1;
    }
    catch (exception &e)
    {
        std::cerr << "exception cout. what:" << e.what() << std::endl;
    }

    return 0;
}