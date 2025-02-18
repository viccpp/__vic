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
    struct group
    {
        uint8_t b[2];
        group &operator=(uint16_t v)
        {
            b[0] = hi(v);
            b[1] = lo(v);
            return *this;
        }
    };
#if __cpp_static_assert
    static_assert(sizeof(group) == 2, "Unexpected padding");
#endif
    group a[8];
    group *p = a, *suffix = nullptr;

    for(int groups_left = 8;; groups_left--)
    {
        if(groups_left <= 0) return false; // too many groups
        if(s == end)
        {
            if(p == suffix) break; // no suffix
            return false; // EOS
        }
        if(*s == ':')
        {
            if(suffix) return false; // duplicated ::
            if(p == a && (++s == end || *s != ':')) return false; // :x
            suffix = p;
            groups_left--; // :: is at least 2 groups
            s++;
            continue;
        }
        uint16_t group = 0;
        for(int i = 0;; i++)
        {
            if(i == 4) return false; // more than 4 digits in the group
            int d = ascii::xdigit_to_number(*s);
            if(d == -1) return false; // not a HEX digit
            group = (group << 4) | uint16_t(d);
            if(++s == end)
            {
                if(groups_left != 1 && !suffix) return false; // too few groups
                *p++ = group;
                goto outer_loop_break;
            }
            if(*s == ':')
            {
                *p++ = group;
                s++;
                break;
            }
        }
    }
outer_loop_break:
    if(suffix)
    {
        size_t pref_n = (suffix - a) * 2,
               suff_n = (p - suffix) * 2,
               zeros_n = 16 - (pref_n + suff_n);
        uint8_t *out = res.s6_addr;
        if(pref_n) { std::memcpy(out, a, pref_n); out += pref_n; }
        std::memset(out, 0, zeros_n); out += zeros_n;
        if(suff_n) std::memcpy(out, suffix, suff_n);
    }
    else std::memcpy(res.s6_addr, a, 16);
    return true;
}
//----------------------------------------------------------------------------

} // namespace
