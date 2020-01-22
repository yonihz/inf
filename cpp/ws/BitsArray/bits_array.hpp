#ifndef _ILRD_RD743_BITS_ARRAY_HPP_
#define _ILRD_RD743_BITS_ARRAY_HPP_

#include <algorithm>
#include <cstddef>
#include <cstring>

#include <bits/stdc++.h>

#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define SET_BITS B6(0), B6(1), B6(1), B6(2)

static size_t set_bits_lut[256] = { SET_BITS };

typedef unsigned long DWORD;

namespace ilrd
{

struct ToggleAll_;
struct BitwiseAnd_;
struct BitwiseOr_;
struct BitwiseXor_;

template<size_t N>
class BitsArray
{
    class BitProxy;

public:
    const static DWORD BIT_DWORD = (CHAR_BIT * sizeof(DWORD));
    const static DWORD N_DWORD = (N/BIT_DWORD) + 1 - ((N%BIT_DWORD) == 0);

    explicit BitsArray();
    ~BitsArray();
    BitsArray(const BitsArray& other_);

    BitsArray& operator=(const BitsArray& other_);
    
    bool operator[](size_t idx_) const;
    BitProxy operator[](size_t idx_);
    
    BitsArray& operator>>=(size_t n_);
    BitsArray& operator<<=(size_t n_);

    BitsArray& operator&=(const BitsArray& other_);
    BitsArray& operator|=(const BitsArray& other_);
    BitsArray& operator^=(const BitsArray& other_);

    bool operator==(const BitsArray& other_);
    bool operator!=(const BitsArray& other_);

    void SetAll(bool val_ = true);
    size_t Count(bool val_ = true) const;

    BitsArray& ToggleAll();
    BitsArray& ToggleOne(size_t idx_);

    BitsArray& SetBit(size_t idx_, bool val_);
    bool GetBit(size_t idx_) const;

private:
    DWORD m_arr[N_DWORD];

    class BitProxy
    {
    public:
        BitProxy(BitsArray& org_, size_t idx_);
        ~BitProxy();
        BitProxy& operator=(BitProxy& rhs_);
        BitProxy& operator=(bool rhs_);
        operator bool() const;
    private:
        BitsArray *m_org;
        DWORD m_idx;
    };
};

template<size_t N>
BitsArray<N>::BitsArray()
    : m_arr() {}

template<size_t N>
BitsArray<N>::~BitsArray() { }

template<size_t N>
BitsArray<N>::BitsArray(const BitsArray<N>& other_)
    : m_arr()
{
    std::copy(other_.m_arr, other_.m_arr + N_DWORD, m_arr);
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator=(const BitsArray<N>& other_)
{
    std::copy(other_.m_arr, other_.m_arr + N_DWORD, m_arr);
}

template<size_t N>
bool BitsArray<N>::operator[](size_t idx_) const
{
    return GetBit();
}

template<size_t N>
typename BitsArray<N>::BitProxy BitsArray<N>::operator[](size_t idx_)
{
    return BitProxy(*this, idx_);
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator>>=(size_t n_)
{

}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator<<=(size_t n_)
{

}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator&=(const BitsArray<N>& other_)
{
    BitwiseAnd_ bitwise_and;
    std::transform(m_arr, m_arr + N_DWORD, (const_cast<BitsArray<N>&>(other_)).m_arr, m_arr, bitwise_and);
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator|=(const BitsArray<N>& other_)
{
    BitwiseOr_ bitwise_or;
    std::transform(m_arr, m_arr + N_DWORD, (const_cast<BitsArray<N>&>(other_)).m_arr, m_arr, bitwise_or);
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator^=(const BitsArray<N>& other_)
{
    BitwiseXor_ bitwise_xor;
    std::transform(m_arr, m_arr + N_DWORD, (const_cast<BitsArray<N>&>(other_)).m_arr, m_arr, bitwise_xor);
}

template<size_t N>
bool BitsArray<N>::operator==(const BitsArray& other_)
{
    return (std::equal(m_arr, m_arr + N_DWORD, other_.m_arr));
}

template<size_t N>
bool BitsArray<N>::operator!=(const BitsArray& other_)
{
   return !(std::equal(m_arr, m_arr + N_DWORD, other_.m_arr));
}

template<size_t N>
void BitsArray<N>::SetAll(bool val_)
{
    std::fill(m_arr, m_arr + N_DWORD, ~(DWORD)val_ + 1ul);
}

template<size_t N>
size_t BitsArray<N>::Count(bool val_) const
{

}

template<size_t N>
BitsArray<N>& BitsArray<N>::ToggleAll()
{
    ToggleAll_ toggle_all;
    std::for_each(m_arr, m_arr + N_DWORD, toggle_all);
    return *this;
}

template<size_t N>
BitsArray<N>& BitsArray<N>::ToggleOne(size_t idx_)
{
    DWORD m = (1 << (idx_ % BIT_DWORD));

    m_arr[idx_ / BIT_DWORD] ^= m;

    return *this;
}

template<size_t N>
BitsArray<N>& BitsArray<N>::SetBit(size_t idx_, bool val_)
{
    DWORD m = (1 << (idx_ % BIT_DWORD));
    m_arr[idx_ / BIT_DWORD] &= (~m);
    m_arr[idx_ / BIT_DWORD] |= (val_ << (idx_ % BIT_DWORD));

    return *this;
}

template<size_t N>
bool BitsArray<N>::GetBit(size_t idx_) const
{
    return (m_arr[idx_ / BIT_DWORD] >> (idx_ % BIT_DWORD)) & 1ul;
}

template<size_t N>
BitsArray<N>::BitProxy::BitProxy(BitsArray &org_, size_t idx_)
    : m_org(&org_), m_idx(idx_) {}

template<size_t N>
BitsArray<N>::BitProxy::~BitProxy() {}

template<size_t N>
typename BitsArray<N>::BitProxy& BitsArray<N>::BitProxy::operator=(BitProxy& rhs_)
{
    m_org->SetBit(m_idx, rhs_.m_org->GetBit(rhs_.m_idx));
    return *this;
}

template<size_t N>
typename BitsArray<N>::BitProxy& BitsArray<N>::BitProxy::operator=(bool rhs_)
{
    m_org->SetBit(m_idx, rhs_);
    return *this;
}

template<size_t N>
BitsArray<N>::BitProxy::operator bool() const
{
    return m_org->GetBit(m_idx);
}

struct CountWord
{
    void operator() (DWORD &elem)
    {
        
    }
};

struct CountChar
{
    void operator() (char &elem)
    {
        
    }
};

struct ToggleAll_
{
    void operator() (DWORD &elem)
    {
        elem ^= (~0);
    }
};

struct BitwiseAnd_
{
    DWORD &operator() (DWORD &elem1, DWORD &elem2)
    {
        return (elem1 &= elem2);
    }
};

struct BitwiseOr_
{
    DWORD &operator() (DWORD &elem1, DWORD &elem2)
    {
        return (elem1 |= elem2);
    }
};

struct BitwiseXor_
{
    DWORD &operator() (DWORD &elem1, DWORD &elem2)
    {
        return (elem1 ^= elem2);
    }
};

} //namespace ilrd

#endif // _ILRD_RD743_BITS_ARRAY_HPP_