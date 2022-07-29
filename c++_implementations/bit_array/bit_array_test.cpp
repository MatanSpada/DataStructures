#include <iostream>             // std::cout, std::endl
#include <cassert>              // assert
#include "bit_array.hpp" // bitarray API
#include "utils.hpp"            // utils
#include <cstring>

using namespace ilrd_rd1145;
using namespace colors;

void ResetBitArray(BitArray<64>& bitArr)
{
    for (size_t i = 0; i < 64; ++i)
    {
        bitArr.Set(i, false);
    }
}

void TestSettersNGet()
{
    BitArray<64> b1;

    std::cout << BOLD_YELLOW << "\nTesting setters:" << std::endl;

    std::cout << BOLD_CYAN << "Testing Set(idx, val)" << BOLD_RED << std::endl;

    b1.Set(34, true);
    assert(b1.Get(34) == true);
    b1.Set(34, false);
    assert(b1.Get(34) == false);

    std::cout << BOLD_GREEN << "Passed!\n" << WHITE << std::endl;

    std::cout << BOLD_CYAN << "Testing Set(idx, val) exception" << BOLD_RED << std::endl;

    try
    {
        b1.Set(65, true);
    }
    catch(const std::out_of_range& ofr)
    {
        std::cout << BOLD_GREEN << "Passed!\n" << WHITE << std::endl; 
    }
    catch(const std::exception& e)
    {
        std::cout << "Failed to catch exception" << std::endl;
        exit(1);
    }

    std::cout << BOLD_CYAN << "Testing Set(idx)" << BOLD_RED << std::endl;

    b1.Set(24);

    assert(b1.Get(24) == true);
    std::cout << BOLD_GREEN << "Passed!\n" << WHITE << std::endl; 

    std::cout << BOLD_CYAN << "Testing Set(idx) exception" << BOLD_RED << std::endl;

    try
    {
        b1.Set(65);
    }
    catch(const std::out_of_range& ofr)
    {
        std::cout << BOLD_GREEN << "Passed!\n" << WHITE << std::endl; 
    }
    catch(const std::exception& e)
    {
        std::cout << "Failed to catch exception" << std::endl;
        exit(1);
    }

    std::cout << BOLD_CYAN << "Testing Set()"<< BOLD_RED << std::endl; 

    b1.Set();
    for (size_t i = 0; i < 64; ++i)
    {
        assert(b1.Get(i) == true);
    }
    std::cout << BOLD_GREEN << "Passed!\n" << WHITE << std::endl;
}

void TestNotEqualNEqual()
{
    BitArray<64> b1;
    BitArray<64> b2;

    std::cout << BOLD_YELLOW << "Testing comparison operators:" << std::endl;

    std::cout << BOLD_CYAN << "Testing operator=="<< BOLD_RED << std::endl; 
    
    assert(b1 == b2);
    std::cout << BOLD_GREEN << "Passed!\n" << WHITE << std::endl; 

    std::cout << BOLD_CYAN << "Testing operator!=" << BOLD_RED << std::endl; 

    b2.Set();

    assert(b1 != b2);
    std::cout << BOLD_GREEN << "Passed!" << WHITE << std::endl; 
}

void TestLogicOperators()
{
    BitArray<64> b1;
    BitArray<64> b2;
    BitArray<64> b3;

    std::cout << BOLD_YELLOW << "\nTesting logical operators:" << std::endl;

    std::cout << BOLD_CYAN << "Testing operator&="<< BOLD_RED << std::endl;
    
    b2.Set(24);
    b3.Set(24);    
    
    b1 &= b2;
    b3 &= b2;

    assert(b1 != b2);
    assert(b3 == b2);
    std::cout << BOLD_GREEN << "Passed!\n" << WHITE << std::endl;

    std::cout << BOLD_CYAN << "Testing operator|="<< BOLD_RED << std::endl;
    
    ResetBitArray(b1);
    ResetBitArray(b2);

    b1.Set(2);
    b2.Set(24);    
    
    b1 |= b2;
    
    b3.Set(2);
    b3.Set(24);

    assert(b1 != b2);
    assert(b3 == b1);
    std::cout << BOLD_GREEN << "Passed!\n" << WHITE << std::endl;

    std::cout << BOLD_CYAN << "Testing operator^="<< BOLD_RED << std::endl;
    
    ResetBitArray(b1);
    ResetBitArray(b2);
    ResetBitArray(b3);
    
    b1.Set(2);
    b1.Set(24);
    b2.Set(2);
    b2.Set(24);

    b1 ^= b2;

    assert(b2 != b1);
    assert(b3 == b1);
    std::cout << BOLD_GREEN << "Passed!\n" << WHITE << std::endl;
}

void TestFlips()
{
    BitArray<64> b1;
    BitArray<64> b2;

    std::cout << BOLD_YELLOW << "Testing flips:" << std::endl;

    std::cout << BOLD_CYAN << "Testing Flip()" << BOLD_RED << std::endl;

    b1.Flip();
    b2.Set();

    assert(b2 == b1);
    std::cout << BOLD_GREEN << "Passed!\n" << WHITE << std::endl;
    
    std::cout << BOLD_CYAN << "Testing Flip(idx)" << BOLD_RED << std::endl;

    b1.Flip(53);
    b2.Set(53, false);

    assert(b2[53] == b1[53]);
    std::cout << BOLD_GREEN << "Passed!\n" << WHITE << std::endl;

    std::cout << BOLD_CYAN << "Testing Flip(idx) exception" << BOLD_RED << std::endl;

    try
    {
        b1.Flip(65);
    }
    catch(const std::out_of_range& ofr)
    {
        std::cout << BOLD_GREEN << "Passed!\n" << WHITE << std::endl; 
    }
    catch(const std::exception& e)
    {
        std::cout << "Failed to catch exception" << std::endl;
        exit(1);
    }
}

void TestCount()
{
    BitArray<64> b1;
    BitArray<70> b2;
    std::cout << BOLD_YELLOW << "Testing Count():" << std::endl;

    std::cout << BOLD_CYAN << "Testing Count()" << BOLD_RED << std::endl;

    b1.Set();
    assert(b1.Count() == 64);

    b2.Set();
    assert(b2.Count() == 70);
    std::cout << BOLD_GREEN << "Passed!\n" << WHITE << std::endl;
}

int main()
{
    TestSettersNGet();
    TestNotEqualNEqual();
    TestLogicOperators();
    TestFlips();
    TestCount();

    std::cout << BOLD_PURPLE << "\nAll done!\n" << WHITE << std::endl;

    return (0);
}