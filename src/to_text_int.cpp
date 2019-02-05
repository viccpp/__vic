//
// $Id$
//

#include<__vic/to_text.h>
#include<__vic/stdint.h>

namespace __vic {

//----------------------------------------------------------------------------
template<class UInt>
inline void append_unsigned_integer(UInt n, std::string &s)
{
    if(n == UInt(0))
    {
        s += '0';
        return;
    }
    char buf[sizeof(n) * 4]; // *3 would be enough but I prefer aligned bufs
    char *p = buf + sizeof buf;
    do {
        *--p = char(n % 10) + '0';
        n /= 10;
    } while(n);
    s.append(p, buf + sizeof buf - p);
}
//----------------------------------------------------------------------------
template<class Int>
inline void append_signed_integer(Int n, std::string &s)
{
    typedef typename uint_exactly_bytes<sizeof(Int)>::type UInt;
    UInt uint_value;
    if(n < Int(0))
    {
        s += '-';
        // two's complement representation is implied
        uint_value = UInt(~n) + UInt(1);
    }
    else uint_value = n;
    append_unsigned_integer(uint_value, s);
}
//----------------------------------------------------------------------------
void to_text_append(long n, std::string &s)
{
    append_signed_integer(n, s);
}
//----------------------------------------------------------------------------
void to_text_append(unsigned long n, std::string &s)
{
    append_unsigned_integer(n, s);
}
//----------------------------------------------------------------------------
void to_text_append(__VIC_LONGLONG n, std::string &s)
{
    append_signed_integer(n, s);
}
//----------------------------------------------------------------------------
void to_text_append(unsigned __VIC_LONGLONG n, std::string &s)
{
    append_unsigned_integer(n, s);
}
//----------------------------------------------------------------------------

} // namespace
