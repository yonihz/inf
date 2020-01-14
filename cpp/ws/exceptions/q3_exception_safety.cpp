#include <iostream>
#include <typeinfo>
#include <exception>

using namespace std;

struct ThrowAtDefCtor
{
	ThrowAtDefCtor()
	{
		cerr << "ThrowAtDefCtor DefCtor" << endl;
		throw bad_cast();
	}
	
	ThrowAtDefCtor(int) { cerr << "ThrowAtDefCtor Ctor (int)" << endl; }
	~ThrowAtDefCtor() { cerr << "ThrowAtDefCtor Dtor" << endl; }
};

struct NoThrow
{
	NoThrow() { cerr << "NoThrow Ctor" << endl; }
	~NoThrow() { cerr << "NoThrow Dtor" << endl; }
};

class X
{
public:
	X() : m_tdc(2) { cerr << "X Ctor" << endl; }
	~X() { cerr << "X dtor" << endl; }

private:
	NoThrow m_nt;
	ThrowAtDefCtor m_tdc;
};

class Y
{
public:
	Y() { cerr << "Y Ctor" << endl; }
	~Y() { cerr << "Y Dtor" << endl; }

private:
	ThrowAtDefCtor m_dtc;
	NoThrow m_nt;
};

class Z
{
public:
	Z() { cerr << "Z Ctor" << endl; }
	~Z() { cerr << "Z Dtor" << endl; }

private:
	NoThrow m_nt;
	ThrowAtDefCtor m_dtc;
};

class YPtrs
{
public:
	YPtrs()
	: m_nt(new NoThrow), m_dtc(new ThrowAtDefCtor)
	{
		cerr << "YPtrs Ctor" << endl; 
	}
	
	~YPtrs()
	{
		cerr << "YPtrs Dtor" << endl;
		delete m_nt;
		delete m_dtc;
	}

private:
	NoThrow *m_nt;
	ThrowAtDefCtor *m_dtc;
};

class ZPtrs
{
public:
	ZPtrs()
	{
		cerr << "ZPtrs Ctor" << endl;
		m_nt = new NoThrow;
		m_dtc = new ThrowAtDefCtor;
	}
	
	~ZPtrs()
	{
		cerr << "ZPtrs Dtor" << endl;
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
		// X var1;
		// Y var1;
		// Z var1;

        // YPtrs yp;
        ZPtrs zp;
	}
	catch (exception &e)
	{
		cerr << "exception cout, what:" << e.what() << endl;
	}

	return 0;
}