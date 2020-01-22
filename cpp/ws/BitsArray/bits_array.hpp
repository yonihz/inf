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
struct CountWord_;

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
    size_t Count(bool val_ = true);

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
    : m_arr() 
{
    // std::cout << "N_DWORD " << N_DWORD << std::endl;
    // std::cout << "BIT_DWORD " << BIT_DWORD << std::endl;
}

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
    return *this;
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
    return *this;
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator|=(const BitsArray<N>& other_)
{
    BitwiseOr_ bitwise_or;
    std::transform(m_arr, m_arr + N_DWORD, (const_cast<BitsArray<N>&>(other_)).m_arr, m_arr, bitwise_or);
    return *this;
}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator^=(const BitsArray<N>& other_)
{
    BitwiseXor_ bitwise_xor;
    std::transform(m_arr, m_arr + N_DWORD, (const_cast<BitsArray<N>&>(other_)).m_arr, m_arr, bitwise_xor);
    return *this;
}

template<size_t N>
bool BitsArray<N>::operator==(const BitsArray& other_)
{
    m_arr[N_DWORD - 1] &= ~((~(DWORD)0) << (N%BIT_DWORD));

    (const_cast<BitsArray&>(other_)).m_arr[N_DWORD - 1] &=
        ~((~(DWORD)0) << (N%BIT_DWORD));

    return (std::equal(m_arr, m_arr + N_DWORD, other_.m_arr));
}

template<size_t N>
bool BitsArray<N>::operator!=(const BitsArray& other_)
{
    m_arr[N_DWORD - 1] &= ~((~(DWORD)0) << (N%BIT_DWORD));

    (const_cast<BitsArray&>(other_)).m_arr[N_DWORD - 1] &=
        ~((~(DWORD)0) << (N%BIT_DWORD));

    return !(std::equal(m_arr, m_arr + N_DWORD, other_.m_arr));
}

template<size_t N>
void BitsArray<N>::SetAll(bool val_)
{
    std::fill(m_arr, m_arr + N_DWORD, ~(DWORD)val_ + 1ul);
}

template<size_t N>
size_t BitsArray<N>::Count(bool val_)
{
    m_arr[N_DWORD - 1] &= ~((~(DWORD)0) << (N%BIT_DWORD));

    CountWord_ count_word;
    size_t count = std::accumulate(m_arr, m_arr + N_DWORD, 0ul, count_word);
    count = val_ ? count : (N - count - ((BIT_DWORD-N%BIT_DWORD)/BIT_DWORD));

    return count;
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
    // std::cout << "idx_ % BIT_DWORD " << (idx_ % BIT_DWORD) << std::endl;
    // std::cout << "idx_ / BIT_DWORD " << (idx_ / BIT_DWORD) << std::endl;
    DWORD m = ((DWORD)1 << (idx_ % BIT_DWORD));
    m_arr[idx_ / BIT_DWORD] &= (~m);
    m_arr[idx_ / BIT_DWORD] |= ((DWORD)val_ << (idx_ % BIT_DWORD));

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

struct CountWord_
{
    size_t operator() (size_t sum, DWORD &elem)
    {
        unsigned char *p = (unsigned char *)&elem;
        sum += set_bits_lut[p[0]] + set_bits_lut[p[1]] + 
            set_bits_lut[p[2]] + set_bits_lut[p[3]] +
            set_bits_lut[p[4]] + set_bits_lut[p[5]] +
            set_bits_lut[p[6]] + set_bits_lut[p[7]];
        
        return sum;
    }
};

struct ToggleAll_
{
    void operator() (DWORD &elem)
    {
        elem ^= ~(DWORD)0;
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