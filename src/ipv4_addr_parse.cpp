//
// $Id$
//

#include<__vic/ip_addr.h>
#include<__vic/str2num.h>

namespace __vic {

//----------------------------------------------------------------------------
// RegExp: (\d{1,3}\.){3}\d{1,3}
bool ipv4_addr::parse(const char *s, const char *end, ::in_addr &res)
{
    uint8_t a[3];
    for(int i = 0; i < 3; i++)
    {
        if(s == end) return false;
        const char *dot = s;
        do
            if(++dot == end) return false;
        while(*dot != '.');

        number_parse_result<uint8_t> r = parse_decimal<uint8_t>(s, dot);
        if(!r) return false;
        a[i] = r.value();

        s = dot + 1;
    }
    number_parse_result<uint8_t> r = parse_decimal<uint8_t>(s, end);
    if(!r) return false;
    res = ipv4_addr(a[0], a[1], a[2], r.value());
    return true;
}
//----------------------------------------------------------------------------

} // namespace
