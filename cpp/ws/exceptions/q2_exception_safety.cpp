int Foo(int) {throw std::bad_alloc; }

void Bar() { throw std::bad_cast;}

X::~X()
{
    std::cerr << Foo(m_a) << std::endl;
}

void Fishi()
{
    X x1;
    
    Bar();
}