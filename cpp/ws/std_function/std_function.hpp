#ifndef _ILRD_RD734_FUNCTION_HPP
#define _ILRD_RD734_FUNCTION_HPP

namespace ilrd
{
template <typename>
class Function;

template <class R, class... Args>
class Function<R(Args...)>
{
public:
    template <class F>
    Function(F fp_); // non-explicit
    ~Function();

    R operator()(Args... args) const;

private:
    R (*m_fp)(Args...);    

    Function(const Function&);
    const Function& operator=(const Function&);
};

template <class R, class... Args>
template <class F>
Function<R(Args...)>::Function(F fp_)
    : m_fp(fp_)
{

}

template <class R, class... Args>
Function<R(Args...)>::~Function()
{
}

template <class R, class... Args>
R Function<R(Args...)>::operator()(Args... args) const
{
    return m_fp(args...);
}

} //namespace ilrd
#endif //_ILRD_RD734_FUNCTION_HPP