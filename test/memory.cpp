#include<__vic/memory.h>
#include<__vic/stdint.h>
#include<iostream>
#include<exception>
#include<cassert>

void load_unaligned_test()
{
    unsigned char bytes[5] = { 0, 0xFF, 0xFF, 0xFF, 0xFF };
    assert(__vic::load_unaligned<uint32_t>(bytes + 1) == 0xFFFFFFFF);
}
void run_tests()
{
    load_unaligned_test();
}

int main()
{
    try
    {
        run_tests();
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
