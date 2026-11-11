//
// $Id$
//

#include<__vic/ip_addr.h>
#include<__vic/ascii.h>
#include<cstring>

namespace __vic {

//----------------------------------------------------------------------------
// Supports full (x:x:x:x:x:x:x:x) and reduced (::) forms
bool ipv6_addr::parse(const char *s, const char *end, ::in6_addr &res)
{
    uint8_t a[16];
    int n = 0;    // number of 16-bit groups parsed
    int gap = -1; // position of "::" (in groups), or -1 if none
    if(s != end && *s == ':') // leading "::"
    {
        if(++s == end || *s != ':') return false; // ":x"
        gap = 0;
        if(++s == end) // just "::"
        {
            std::memset(res.s6_addr, 0, 16);
            return true;
        }
    }
    for(;;)
    {
        if(n == 8) return false; // too many groups
        const char *group = s;
        unsigned v = 0;
        int digits = 0;
        for(; s != end; s++, digits++)
        {
            int d = ascii::xdigit_to_number(*s);
            if(d == -1) break;
            if(digits == 4) return false; // more than 4 digits in the group
            v = (v << 4) | unsigned(d);
        }
        if(s != end && *s == '.') // embedded IPv4 address (must be the last)
        {
            ::in_addr ip4;
            if(n > 6 || !ipv4_addr::parse(group, end, ip4)) return false;
            std::memcpy(a + 2*n, &ip4.s_addr, 4);
            n += 2;
            break;
        }
        if(digits == 0) return false; // empty group or not a HEX digit
        a[2*n] = uint8_t(v >> 8);
        a[2*n + 1] = uint8_t(v & 0xFFU);
        n++;
        if(s == end) break;
        if(*s != ':' || ++s == end) return false; // junk or trailing ':'
        if(*s == ':') // "::"
        {
            if(gap != -1) return false; // duplicated "::"
            gap = n;
            if(++s == end) break; // trailing "::"
        }
    }
    if(gap == -1)
    {
        if(n != 8) return false; // too few groups
        std::memcpy(res.s6_addr, a, 16);
        return true;
    }
    // RFC 5952 forbids using :: to shorten just one 16-bit 0 field for ENCODERS!
    // Decoders must still accept any encoding that complies with RFC 4291
    if(n > 7) return false; // "::" must stand for at least one group (RFC 4291)
    int pref_n = gap * 2, suff_n = (n - gap) * 2, zeros_n = 16 - pref_n - suff_n;
    std::memcpy(res.s6_addr, a, pref_n);
    std::memset(res.s6_addr + pref_n, 0, zeros_n);
    std::memcpy(res.s6_addr + pref_n + zeros_n, a + pref_n, suff_n);
    return true;
}
//----------------------------------------------------------------------------

} // namespace
