#include<__vic/endian.h>
#include<iostream>
#include<exception>
#include<cstring>
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

    const uint8_t bytes[4] = { 0x01, 0x02, 0x03, 0x04 };
    uint32_t n;
    std::memcpy(&n, bytes, 4);
    assert(__vic::endian::from_big(n)    == 0x01020304);
    assert(__vic::endian::from_little(n) == 0x04030201);

#if __cplusplus >= 201103L // C++11
    enum class En : uint32_t
    {
        be_value = 0x01020304,
        le_value = 0x04030201
    };
    En en;
    std::memcpy(&en, bytes, 4);
    assert(__vic::endian::from_big(en)    == En::be_value);
    assert(__vic::endian::from_little(en) == En::le_value);
#endif
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
