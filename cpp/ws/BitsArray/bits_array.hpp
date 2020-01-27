#ifndef _ILRD_RD743_BITS_ARRAY_HPP_
#define _ILRD_RD743_BITS_ARRAY_HPP_

#include <algorithm>    // for_each, accumulate, fill, transform, copy

#include <bits/stdc++.h>    // CHAR_BIT

// Set Bits char LUT

#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define SET_BITS B6(0), B6(1), B6(1), B6(2)

static size_t set_bits_lut[256] = { SET_BITS };

// typedef of the word type used
typedef unsigned long DWORD;

namespace ilrd
{

template<size_t N>
class BitsArray
{
    class BitProxy;

public:

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

    const static DWORD BIT_DWORD = (CHAR_BIT * sizeof(DWORD));
    const static DWORD N_DWORD = (N/BIT_DWORD) + 1 - ((N%BIT_DWORD) == 0);
    const static DWORD UNUSED_BITS_MASK = ~((~(static_cast<DWORD>(0))) << (N % BIT_DWORD));

    DWORD m_arr[N_DWORD];

    void FixTail();

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

// Functors
struct ToggleWord;
struct BitwiseAnd;
struct BitwiseOr;
struct BitwiseXor;
struct CountWord;

/**
 * @brief Construct a new Bits Array< N>:: Bits Array object
 * 
 * @tparam N number of bits in array
 */

template<size_t N>
BitsArray<N>::BitsArray()
    : m_arr() {}

/**
 * @brief Destroy the Bits Array< N>:: Bits Array object
 * 
 * @tparam N 
 */

template<size_t N>
BitsArray<N>::~BitsArray() { }

/**
 * @brief Construct a new Bits Array< N>:: Bits Array object by copying
 * another Bits Array object
 * 
 * @tparam N 
 * @param other_ Bits Array object
 */

template<size_t N>
BitsArray<N>::BitsArray(const BitsArray<N>& other_)
    : m_arr()
{
    std::copy(other_.m_arr, other_.m_arr + N_DWORD, m_arr);
}

/**
 * @brief Assignment operator that takes an equally sized Bits Array object
 * 
 * @tparam N 
 * @param other_ Bits Array object
 * @return BitsArray<N>& - newly assigned object
 */

template<size_t N>
BitsArray<N>& BitsArray<N>::operator=(const BitsArray<N>& other_)
{
    std::copy(other_.m_arr, other_.m_arr + N_DWORD, m_arr);
    return *this;
}

/**
 * @brief operator[] returns value at position idx_
 * 
 * @tparam N 
 * @param idx_ 
 */

template<size_t N>
bool BitsArray<N>::operator[](size_t idx_) const
{
    return GetBit(idx_);
}

/**
 * @brief operator[] returns a modifiable BitProxy object 
 * 
 * @tparam N 
 * @param idx_ 
 * @return BitsArray<N>::BitProxy 
 */

template<size_t N>
typename BitsArray<N>::BitProxy BitsArray<N>::operator[](size_t idx_)
{
    return BitProxy(*this, idx_);
}

/**
 * @brief Shift right operator by n_ bits
 * 
 * @tparam N 
 * @param n_ 
 * @return BitsArray<N>& 
 */

template<size_t N>
BitsArray<N>& BitsArray<N>::operator>>=(size_t n_)
{

}

/**
 * @brief Shift right operator by n_ bits
 * 
 * @tparam N 
 * @param n_ 
 * @return BitsArray<N>& 
 */

template<size_t N>
BitsArray<N>& BitsArray<N>::operator<<=(size_t n_)
{

}

/**
 * @brief Bitwise AND (&) operator between another Bits Array object. Returns
 * the modified Bits Array object
 * 
 * @tparam N 
 * @param other_ 
 * @return BitsArray<N>& 
 */

template<size_t N>
BitsArray<N>& BitsArray<N>::operator&=(const BitsArray<N>& other_)
{
    std::transform(m_arr, m_arr + N_DWORD, other_.m_arr, m_arr, BitwiseAnd());
    return *this;
}

/**
 * @brief Bitwise OR (|) operator between another Bits Array object. Returns
 * the modified Bits Array object
 * 
 * @tparam N 
 * @param other_ 
 * @return BitsArray<N>& 
 */
template<size_t N>
BitsArray<N>& BitsArray<N>::operator|=(const BitsArray<N>& other_)
{
    std::transform(m_arr, m_arr + N_DWORD, other_.m_arr, m_arr, BitwiseOr());
    return *this;
}

/**
 * @brief Bitwise XOR (^) operator between another Bits Array object. Returns
 * the modified Bits Array object
 * 
 * @tparam N 
 * @param other_ 
 * @return BitsArray<N>& 
 */

template<size_t N>
BitsArray<N>& BitsArray<N>::operator^=(const BitsArray<N>& other_)
{
    std::transform(m_arr, m_arr + N_DWORD, other_.m_arr, m_arr, BitwiseXor());
    return *this;
}

/**
 * @brief Check if both Bits Array objects are equal
 * 
 * @tparam N 
 * @param other_ 
 * @return true 
 * @return false 
 */

template<size_t N>
bool BitsArray<N>::operator==(const BitsArray& other_)
{
    return (std::equal(m_arr, m_arr + N_DWORD, other_.m_arr));
}

/**
 * @brief Check if both Bits Array objects are not equal
 * 
 * @tparam N 
 * @param other_ 
 * @return true 
 * @return false 
 */

template<size_t N>
bool BitsArray<N>::operator!=(const BitsArray& other_)
{
    return !(*this == other_);
}

/**
 * @brief Set all bits in array to val_
 * 
 * @tparam N 
 * @param val_ 
 */

template<size_t N>
void BitsArray<N>::SetAll(bool val_)
{
    std::fill(m_arr, m_arr + N_DWORD, ~(static_cast<DWORD>(val_)) + static_cast<DWORD>(1));
    FixTail();
}

/**
 * @brief Count all bits in array that are set to val_
 * 
 * @tparam N 
 * @param val_ 
 * @return size_t 
 */

template<size_t N>
size_t BitsArray<N>::Count(bool val_)
{
    size_t count = std::accumulate(m_arr, m_arr + N_DWORD, static_cast<DWORD>(0), CountWord());
    count = val_ ? count : (N - count);

    return count;
}

/**
 * @brief Flip all bits in array
 * 
 * @tparam N 
 * @return BitsArray<N>& 
 */

template<size_t N>
BitsArray<N>& BitsArray<N>::ToggleAll()
{
    std::for_each(m_arr, m_arr + N_DWORD, ToggleWord());
    FixTail();
    return *this;
}

/**
 * @brief Flip bit at position idx_ in array
 * 
 * @tparam N 
 * @param idx_ 
 * @return BitsArray<N>& 
 */

template<size_t N>
BitsArray<N>& BitsArray<N>::ToggleOne(size_t idx_)
{
    DWORD m = (static_cast<DWORD>(1) << (idx_ % BIT_DWORD));

    m_arr[idx_ / BIT_DWORD] ^= m;

    return *this;
}

/**
 * @brief Set bit in position idx_ to val_
 * 
 * @tparam N 
 * @param idx_ 
 * @param val_ 
 * @return BitsArray<N>& 
 */

template<size_t N>
BitsArray<N>& BitsArray<N>::SetBit(size_t idx_, bool val_)
{
    DWORD m = (static_cast<DWORD>(1) << (idx_ % BIT_DWORD));
    m_arr[idx_ / BIT_DWORD] &= (~m);
    m_arr[idx_ / BIT_DWORD] |= (static_cast<DWORD>(val_) << (idx_ % BIT_DWORD));

    return *this;
}

/**
 * @brief Get value of bit in position idx_
 * 
 * @tparam N 
 * @param idx_ 
 * @return true 
 * @return false 
 */

template<size_t N>
bool BitsArray<N>::GetBit(size_t idx_) const
{
    return (m_arr[idx_ / BIT_DWORD] >> (idx_ % BIT_DWORD)) & static_cast<DWORD>(1);
}

/**
 * @brief Construct a new Bits Array< N>:: Bit Proxy:: Bit Proxy object
 * 
 * @tparam N 
 * @param org_ 
 * @param idx_ 
 */

template<size_t N>
BitsArray<N>::BitProxy::BitProxy(BitsArray &org_, size_t idx_)
    : m_org(&org_), m_idx(idx_) {}

/**
 * @brief Destroy the Bits Array< N>:: Bit Proxy:: Bit Proxy object
 * 
 * @tparam N 
 */

template<size_t N>
BitsArray<N>::BitProxy::~BitProxy() {}

/**
 * @brief Assignment operator that takes another BitProxy object of an equally sized Bits Array
 * 
 * @tparam N 
 * @param rhs_ 
 * @return BitsArray<N>::BitProxy& 
 */

template<size_t N>
typename BitsArray<N>::BitProxy& BitsArray<N>::BitProxy::operator=(BitProxy& rhs_)
{
    m_org->SetBit(m_idx, rhs_);
    return *this;
}

/**
 * @brief Assignment operator that takes a bool value rhs_
 * 
 * @tparam N 
 * @param rhs_ 
 * @return BitsArray<N>::BitProxy& 
 */

template<size_t N>
typename BitsArray<N>::BitProxy& BitsArray<N>::BitProxy::operator=(bool rhs_)
{
    m_org->SetBit(m_idx, rhs_);
    return *this;
}

/**
 * @brief Conversion to bool
 * 
 * @tparam N 
 * @return true 
 * @return false 
 */

template<size_t N>
BitsArray<N>::BitProxy::operator bool() const
{
    return m_org->GetBit(m_idx);
}

// Functors

struct CountWord
{
    size_t operator() (size_t sum, DWORD &elem)
    {
        unsigned char *p = (unsigned char *)&elem;
        
        for (size_t i = 0; i < sizeof(DWORD); ++i)
        {
            sum += set_bits_lut[p[i]];
        }

        return sum;
    }
};

struct ToggleWord
{
    void operator() (DWORD &elem)
    {
        elem ^= ~(static_cast<DWORD>(0));
    }
};

struct BitwiseAnd
{
    DWORD operator() (DWORD elem1, DWORD elem2)
    {
        return (elem1 &= elem2);
    }
};

struct BitwiseOr
{
    DWORD operator() (DWORD elem1, DWORD elem2)
    {
        return (elem1 |= elem2);
    }
};

struct BitwiseXor
{
    DWORD operator() (DWORD elem1, DWORD elem2)
    {
        return (elem1 ^= elem2);
    }
};

/**
 * @brief Set all unused bits in array to 0, for valid count and
 * comparison operations
 * 
 * @tparam N 
 */

template<size_t N>
inline void BitsArray<N>::FixTail()
{
    m_arr[N_DWORD - 1] &= UNUSED_BITS_MASK;    
}

} //namespace ilrd

#endif // _ILRD_RD743_BITS_ARRAY_HPP_










// struct ShiftLeftWords_
// {
//     DWORD operator() (DWORD elem1, DWORD elem2)
//     {
//         return (elem2);
//     }
// };

// struct SetOffWord_
// {
//     DWORD operator() (DWORD elem)
//     {
//         return (elem & static_cast<DWORD>(0));
//     }
// };

// template<size_t N>
// BitsArray<N>& BitsArray<N>::operator<<=(size_t n_)
// {
//     if (n_ >= N)
//     {
//         return *this;
//     }

//     ShiftLeftWords_ shiftw_left;
//     SetOffWord_ setoff_word;
//     std::transform(m_arr, (m_arr + n_ - (n_ / BIT_DWORD)), (m_arr + (n_ / BIT_DWORD)) ,shiftw_left));
//     std::for_each((m_arr + n_ - (n_ / BIT_DWORD)) + 1, m_arr + N_DWORD, setoff_word);
//     std::transform(m_arr + 1, (m_arr + n_ - (n_ / BIT_DWORD)), (m_arr + (n_ / BIT_DWORD)) ,shift_left));
// }