#ifndef ILRD_RD1145_BIT_ARRAY_HPP
#define ILRD_RD1145_BIT_ARRAY_HPP

#include <cstddef> // std::size_t
#include <climits> // CHAR_BIT
#include <string> // for std::string
#include <algorithm>
#include <stdexcept> // out_of_range
#include <cstring> // memset

#if (__cplusplus <= 199711L)
#define noexcept throw()
#endif


#define NUM_OF_SIZE_T(SIZE) ( SIZE/(CHAR_BIT*sizeof(std::size_t)) + !!(SIZE%(CHAR_BIT*sizeof(std::size_t))) )
//#define PLACE(m_bit) ( (m_bit / (CHAR_BIT*sizeof(std::size_t))) )

namespace ilrd_rd1145
{

static const size_t BITS_IN_WORD = sizeof(size_t) * CHAR_BIT; 
//static const NUM_OF_WORDS = (SIZE + BITS_IN_WORD - 1) / BITS_IN_WORD;
static const std::string oob_msg = "OUT OF BOUND.";


template <size_t SIZE>
class BitArray
{
private:
    class BitProxy;

public:
    explicit BitArray();

    bool operator[](std::size_t idx) const; // throw std::out_of_range
    BitProxy operator[](std::size_t idx); // throw std::out_of_range

    BitArray& operator|=(const BitArray& rhs) noexcept;
    BitArray& operator&=(const BitArray& rhs) noexcept;
    BitArray& operator^=(const BitArray& rhs) noexcept;

    bool operator==(const BitArray& other) const noexcept;
    bool operator!=(const BitArray& other) const noexcept;

    BitArray& Set() noexcept;
    BitArray& Set(std::size_t idx); // throw std::out_of_range
    BitArray& Set(std::size_t idx, bool val); // throw std::out_of_range
    BitArray& Flip() noexcept;
    BitArray& Flip(std::size_t idx); // throw std::out_of_range
    bool Get(std::size_t idx) const; // throw std::out_of_range
    std::size_t Count() const noexcept;
    std::string ToString() const; // throw std::bad_alloc //advanced
    BitArray& operator>>=(std::size_t shift); // advanced
    BitArray& operator<<=(std::size_t shift); // advanced

private:
    size_t m_array[NUM_OF_SIZE_T(SIZE)];
    //BitArray& ResetExtraBits() noexcept;

    class BitProxy
    {
    public:
        explicit BitProxy(BitArray& ref, std::size_t idx);
        BitProxy& operator=(bool b);
        BitProxy& operator=(const BitArray::BitProxy& other);
        operator bool() const;

    private:
        BitArray& m_bit_array;
        std::size_t m_idx;
    };
};




/***************** end of class ******************/
/*template <size_t SIZE>
BitArray& BitArray<SIZE>ResetExtraBits() noexcept
{

}*/



// CTOR
template <size_t SIZE>
BitArray<SIZE>::BitArray()
{
    memset(m_array, 0, sizeof(m_array));     // m_array(0)
}


template <size_t SIZE>
bool BitArray<SIZE>::operator[](std::size_t idx) const                        // throw std::out_of_range
{
    if (idx >= SIZE)
    {
        throw std::out_of_range(oob_msg);
    }

    return (m_array[idx / BITS_IN_WORD] & (1UL << (idx & (BITS_IN_WORD - 1)))); // instead of % (and the -1 after the BITS_IN_WORD)
}


template <size_t SIZE>
typename BitArray<SIZE>::BitProxy BitArray<SIZE>::operator[](std::size_t idx)        // throw std::out_of_range
{
    if (idx >= SIZE)
    {
        throw std::out_of_range(oob_msg);
    }

    return BitArray::BitProxy(*this, idx);    
}


/********************** BitProxy ***********************/

template <size_t SIZE>
BitArray<SIZE>::BitProxy::BitProxy(BitArray& arr, std::size_t idx) : m_bit_array(arr), m_idx(idx)
{
    // empty
}


template <size_t SIZE>
typename BitArray<SIZE>::BitProxy& BitArray<SIZE>::BitProxy::operator=(const BitProxy& other) 
{
    return *this = bool(other);
}


template <size_t SIZE>
typename BitArray<SIZE>::BitProxy& BitArray<SIZE>::BitProxy::operator=(bool b)                   //understand
{
    m_bit_array.m_array[m_idx / BITS_IN_WORD] = ((m_bit_array.m_array[m_idx / BITS_IN_WORD]) & ~(1UL << m_idx % BITS_IN_WORD)) | (size_t(b) << m_idx % BITS_IN_WORD);

    return *this;
}

template <size_t SIZE>
BitArray<SIZE>::BitProxy::operator bool() const
{
    return static_cast< const BitArray& >(m_bit_array)[m_idx];          // cast cause we need to use the []
}

/************************************************/


/********* operator |= *********/
class OperatorOR
{
public:
    explicit OperatorOR(size_t *ptr);
    std::size_t operator()(size_t element);

private:
    size_t *m_array;
};

OperatorOR::OperatorOR(size_t *ptr) : m_array(ptr)
{
    //empty
}

std::size_t OperatorOR::operator()(size_t element)
{
    *m_array |= element;
    ++m_array;
    return 0;
}

template <size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator|=(const BitArray& rhs) noexcept
{
    //OperatorOR or1(m_array);
    std::for_each(rhs.m_array, rhs.m_array + NUM_OF_SIZE_T(SIZE), OperatorOR(m_array));

    return *this;
}


/********* operator &= *********/
class OperatorAND
{
public:
    explicit OperatorAND(size_t *ptr);
    std::size_t operator()(size_t element);

private:
    size_t *m_array;
};

OperatorAND::OperatorAND(size_t *ptr) : m_array(ptr)
{
    //empty
}

std::size_t OperatorAND::operator()(size_t element)
{
    *m_array &= element;
    ++m_array;
    return 0;
}

template <size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator&=(const BitArray& rhs) noexcept
{
    //OperatorAND AND1(m_array);
    std::for_each(rhs.m_array, rhs.m_array + NUM_OF_SIZE_T(SIZE), OperatorAND(m_array));

    return *this;
}



/********* operator ^= *********/
class OperatorXOR
{
public:
    explicit OperatorXOR(size_t *ptr);
    std::size_t operator()(size_t element);

private:
    size_t *m_array;
};

OperatorXOR::OperatorXOR(size_t *ptr) : m_array(ptr)
{
    //empty
}

std::size_t OperatorXOR::operator()(size_t element)
{
    *m_array ^= element;
    ++m_array;
    return 0;
}

template <size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator^=(const BitArray& rhs) noexcept
{
    std::for_each(rhs.m_array, rhs.m_array + NUM_OF_SIZE_T(SIZE), OperatorXOR(m_array));

    return *this;
}



/************************************************/
template<std::size_t SIZE>
bool BitArray<SIZE>::operator==(const BitArray& other) const noexcept
{
    return std::equal(m_array, m_array + NUM_OF_SIZE_T(SIZE), other.m_array);
}

template<std::size_t SIZE>
bool BitArray<SIZE>::operator!=(const BitArray& other) const noexcept
{
    return !(m_array == other.m_array);
}


/***************************************************/
template <size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::Set() noexcept
{
    memset(m_array, -1, sizeof(m_array));
    //*m_array = m_array & SIZE;

    size_t num_of_bits = NUM_OF_SIZE_T(SIZE) * sizeof(size_t) * CHAR_BIT; //move to returned func....
    m_array[NUM_OF_SIZE_T(SIZE) - 1] >>= num_of_bits - SIZE; //move to returned func....

    return *this; // ResetRedBits();
}

template <size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::Set(std::size_t idx)
{
    if (idx >= SIZE)
    {
        throw std::out_of_range(oob_msg);
    }

    (*this)[idx] = true;

    return *this;
}


template <size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::Set(std::size_t idx, bool val)
{
    (*this)[idx] = val;

    return *this;
}


template <size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::Flip() noexcept
{   
    size_t num_of_bits = NUM_OF_SIZE_T(SIZE) * sizeof(size_t) * CHAR_BIT;
    *this ^= BitArray().Set();
    m_array[1] <<= num_of_bits;
    m_array[1] >>= num_of_bits;

    return *this;
    
    //return ResetRedBits();
}


template <size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::Flip(std::size_t idx)
{
    (*this)[idx] = !(*this)[idx];

    return *this;
}


template<std::size_t SIZE>
bool BitArray<SIZE>::Get(std::size_t idx) const
{
    return (*this)[idx];
}

class CountFunctor
{
public:
    explicit CountFunctor(size_t& counter);
    void operator()(unsigned char word);

private:
    static const unsigned char LUT[UCHAR_MAX + 1];
    size_t& m_counter;
};

CountFunctor::CountFunctor(size_t& counter) : m_counter(counter)
{
    // empty
}


void CountFunctor::operator()(unsigned char byte)
{
    m_counter += LUT[byte];
}


template <size_t SIZE>
size_t BitArray<SIZE>::Count() const noexcept
{
    size_t counter = 0;
    std::for_each(reinterpret_cast<const unsigned char *>(m_array), 
                  reinterpret_cast<const unsigned char *>(m_array + NUM_OF_SIZE_T(SIZE)), 
                  CountFunctor(counter));

    return counter;
}


const unsigned char CountFunctor::LUT[UCHAR_MAX + 1] = 
{
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8 
};


template <size_t SIZE>
std::string BitArray<SIZE>::ToString() const
{
    std::string result;      // might throw badAlloc
    result.reserve(SIZE);   // might throw badAlloc

    for (size_t i = 0; i < SIZE; ++i)
    {
        result.push_back('0' + (*this)[i]);
    }

    return result;
}


} // ilrd_rd1145

#endif // ILRD_RD1145_BIT_ARRAY_HPP

