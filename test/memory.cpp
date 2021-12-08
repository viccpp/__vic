#include<__vic/memory.h>
#include<__vic/stdint.h>
#include<iostream>
#include<exception>
#include<cassert>

void load_unaligned_test()
{
    unsigned char bytes[5] = { 0, 0xFE, 0xFE, 0xFE, 0xFE };
    assert(__vic::load_unaligned<uint32_t>(bytes + 1) == 0xFEFEFEFE);
}
void store_unaligned_test()
{
    unsigned char bytes[5] = {};
    __vic::store_unaligned<uint32_t>(bytes + 1, 0xFEFEFEFE);
    assert(bytes[1] == 0xFE && bytes[2] == 0xFE
        && bytes[3] == 0xFE && bytes[4] == 0xFE);
}
void run_tests()
{
    load_unaligned_test();
    store_unaligned_test();
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
