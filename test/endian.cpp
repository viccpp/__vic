#include<__vic/endian.h>
#include<iostream>
#include<exception>
#include<cassert>

namespace tests {

//----------------------------------------------------------------------------
const char *endian_str()
{
    namespace endian = __vic::endian;
    switch(endian::native)
    {
        case endian::little: return "little";
        case endian::big: return "big";
        case endian::pdp: return "PDP";
        default: return "?";
    }
}
//----------------------------------------------------------------------------
void run()
{
    std::cout << "Endian is " << endian_str() << '\n';

    assert(__vic::swab16(0x0102) == 0x0201);
    assert(__vic::swab32(0x01020304) == 0x04030201);
    assert(__vic::swab64(0x0102030405060708) == 0x0807060504030201);
}
//----------------------------------------------------------------------------

} // namespace

int main()
{
    try
    {
        tests::run();
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
