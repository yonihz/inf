#include <cstdlib>

namespace math
{
long Fibo(int n);
double Sin(double d);
double Cos(double d);
} //namespace math

namespace fibonacci
{
long lookupTable[256];
long Fibo(int n);

namespace altverstion
{
long Fibo(size_t n);
} //namespace altversion

} //namespace //fibonacci

namespace math
{
double Tang(double d);
}

void A()
{
    int n = 3;
    fibonacci::Fibo(n);
    using math::Fibo;
    Fibo(n);

    math::Sin(3.14);
    math::Tang(3.14);
}

using namespace math;
using namespace fibonacci;
namespace alt = fibonacci::altverstion;

void B()
{
    size_t n = 3;
    alt::Fibo(n);
    math::Fibo(n); //try uncommenting this line, solve the error
    Cos(n); //why doesnt this line create an error?
}