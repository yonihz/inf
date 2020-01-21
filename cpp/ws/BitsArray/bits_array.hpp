#ifndef _ILRD_RD743_BITS_ARRAY_HPP_
#define _ILRD_RD743_BITS_ARRAY_HPP_

#include <algorithm>
#include <cstddef>
#include <cstring>

typedef unsigned long DWORD;

namespace ilrd
{

template<size_t N>
class BitsArray
{
    class BitProxy;

public:
    explicit BitsArray(size_t size_);
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
    DWORD m_arr[(N / sizeof(DWORD)) + 1 - ((N % sizeof(DWORD)) == 0)];

    class BitProxy
    {
    public:
        BitProxy(BitsArray& org_, size_t idx_);
        ~BitProxy();
        BitProxy& operator=(BitProxy& rhs_);
        BitProxy& operator=(bool rhs_);
        operator bool() const;
        // void Flip();
        // bool operator~() const;
    };
};

template<size_t N>
BitsArray<N>::BitsArray(size_t size_)
    : m_arr() { }

template<size_t N>
BitsArray<N>::~BitsArray() { }

template<size_t N>
BitsArray<N>::BitsArray(const BitsArray<N>& other_)
    : m_arr(other_.m_arr) { }

template<size_t N>
BitsArray<N>& BitsArray<N>::operator=(const BitsArray<N>& other_)
{
    memcpy(&m_arr, &other_.m_arr, sizeof(m_arr));
}

template<size_t N>
bool BitsArray<N>::operator[](size_t idx_) const
{
    return m_arr[idx_];
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

}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator|=(const BitsArray<N>& other_)
{

}

template<size_t N>
BitsArray<N>& BitsArray<N>::operator^=(const BitsArray<N>& other_)
{

}

template<size_t N>
bool BitsArray<N>::operator==(const BitsArray& other_)
{

}

template<size_t N>
bool BitsArray<N>::operator!=(const BitsArray& other_)
{

}

template<size_t N>
void BitsArray<N>::SetAll(bool val_)
{

}

template<size_t N>
size_t BitsArray<N>::Count(bool val_) const
{

}

template<size_t N>
BitsArray<N>& BitsArray<N>::ToggleAll()
{

}

template<size_t N>
BitsArray<N>& BitsArray<N>::ToggleOne(size_t idx_)
{

}

template<size_t N>
BitsArray<N>& BitsArray<N>::SetBit(size_t idx_, bool val_)
{

}

template<size_t N>
bool BitsArray<N>::GetBit(size_t idx_) const
{

}

template<size_t N>
typename BitsArray<N>::BitProxy::BitProxy(BitsArray &org_, size_t idx_)
{

}

template<size_t N>
typename BitsArray<N>::BitProxy::~BitProxy()
{

}

template<size_t N>
typename BitsArray<N>::BitProxy& BitsArray<N>::BitProxy::operator=(BitProxy& rhs_)
{

}

template<size_t N>
typename BitsArray<N>::BitProxy& BitsArray<N>::BitProxy::operator=(bool rhs_)
{

}

template<size_t N>
BitsArray<N>::BitProxy::operator bool() const
{

}

} //namespace ilrd

#endif // _ILRD_RD743_BITS_ARRAY_HPP_