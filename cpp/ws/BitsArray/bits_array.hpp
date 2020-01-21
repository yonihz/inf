#ifndef _ILRD_RD743_BITS_ARRAY_HPP_
#define _ILRD_RD743_BITS_ARRAY_HPP_

#include <cstddef>

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

    void SetAll(bool val_ = true);
    size_t Count(bool val_ = true) const;

    BitsArray& ToggleAll();
    BitsArray& ToggleOne(size_t idx_);

    BitsArray& SetBit(size_t idx_, bool val_);
    bool GetBit(size_t idx_) const;

private:
    unsigned long m_arr[N/sizeof(unsigned long) + 1];

    class BitProxy
    {
    public:
        BitProxy(BitsArray& org_, size_t idx_);
        ~BitProxy();
        BitProxy& operator=(BitProxy& rhs_);
        BitProxy& operator=(bool rhs_);
        // operator bool() const;
        // void Flip();
        // bool operator~() const;
    };
};

template<size_t N>
BitsArray<N>::BitsArray(size_t size_)
{

}

template<size_t N>
BitsArray::~BitsArray()
{

}

template<size_t N>
BitsArray::BitsArray(const BitsArray& other_)
{

}

template<size_t N>
BitsArray& BitsArray::operator=(const BitsArray& other_)
{

}

template<size_t N>
bool BitsArray::operator[](size_t idx_) const
{

}

template<size_t N>
BitProxy BitsArray::operator[](size_t idx_)
{

}

template<size_t N>
BitsArray& BitsArray::operator>>=(size_t n_)
{

}

template<size_t N>
BitsArray& BitsArray::operator<<=(size_t n_)
{

}

template<size_t N>
BitsArray& BitsArray::operator&=(const BitsArray& other_)
{

}

template<size_t N>
BitsArray& BitsArray::operator|=(const BitsArray& other_)
{

}

template<size_t N>
BitsArray& BitsArray::operator^=(const BitsArray& other_)
{

}

template<size_t N>
bool BitsArray::operator==(const BitsArray& other_)
{

}

template<size_t N>
void BitsArray::SetAll(bool val_ = true)
{

}

template<size_t N>
size_t BitsArray::Count(bool val_ = true) const
{

}

template<size_t N>
BitsArray& BitsArray::ToggleAll()
{

}

template<size_t N>
BitsArray& BitsArray::ToggleOne(size_t idx_)
{

}

template<size_t N>
BitsArray& BitsArray::SetBit(size_t idx_, bool val_);
bool GetBit(size_t idx_) const;


BitProxy(BitsArray& org_, size_t idx_)
{

}

~BitProxy()
{

}

BitProxy& operator=(BitProxy& rhs_)
{

}

BitProxy& operator=(bool rhs_)
{

}

// operator bool() const;
// void Flip();
// bool operator~() const;

} //namespace ilrd

#endif // _ILRD_RD743_BITS_ARRAY_HPP_