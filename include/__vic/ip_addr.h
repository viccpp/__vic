// IPv4 & IPv6 address
//
// Platform: ISO C++ 98/11/14 - BSD Socket API
// $Id$
//
// (c) __vic 2019

#ifndef __VIC_IP_ADDR_H
#define __VIC_IP_ADDR_H

#include<__vic/defs.h>
#include<__vic/memory.h>
#include<__vic/stdint.h>
#include<string>
#ifdef __MINGW32__
#include<windef.h>
#include<inaddr.h>
#include<in6addr.h>
#else
#include<winsock2.h>
#include<ipexport.h>
#endif
#if __has_include(<string_view>)
#include<string_view>
#endif
#include<functional> // for std::hash
#include<cstring> // for std::memcpy

namespace __vic {

typedef ULONG in_addr_t;

//////////////////////////////////////////////////////////////////////////////
class ipv4_addr : public ::in_addr
{
    __VIC_CONSTEXPR_FUNC static in_addr_t to_in_addr_t(
                                   uint8_t a, uint8_t b, uint8_t c, uint8_t d)
    {
        return (in_addr_t(d) << 24) | (in_addr_t(c) << 16) |
               (in_addr_t(b) << 8 ) |  in_addr_t(a);
    }
public:
    ipv4_addr() __VIC_DEFAULT_CTR
    __VIC_CONSTEXPR_FUNC ipv4_addr(::in_addr a) : in_addr(a) {}
    __VIC_CONSTEXPR_FUNC explicit ipv4_addr(in_addr_t a)
#if __cpp_constexpr == 200704 // C++11
        : in_addr{{{uint8_t(a & 0xFF), uint8_t((a >> 8) & 0xFF), // UB: type punning
                    uint8_t((a >> 16) & 0xFF), uint8_t(a >> 24)}}} {}
#else
        { this->s_addr = a; }
#endif

    __VIC_CONSTEXPR_FUNC ipv4_addr(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
#if __cpp_constexpr
        : ipv4_addr(to_in_addr_t(a, b, c, d)) {}
#else
        { *this = ipv4_addr(to_in_addr_t(a, b, c, d)); }
#endif

    static __VIC_CONSTEXPR_FUNC ipv4_addr any() { return ipv4_addr(0); }
    static __VIC_CONSTEXPR_FUNC ipv4_addr loopback() { return ipv4_addr(127,0,0,1); }

    __VIC_CONSTEXPR_FUNC bool is_any() const { return this->s_addr == 0; }
    __VIC_CONSTEXPR_FUNC bool is_loopback() const
    {
        return this->s_addr == to_in_addr_t(127,0,0,1);
    }

    static bool parse(const char * , const char * , ::in_addr & );
#if __cpp_lib_string_view
    static bool parse(std::string_view s, ::in_addr &res)
        { return parse(s.data(), s.data() + s.length(), res); }
#else
    static bool parse(const std::string &s, ::in_addr &res)
        { return parse(s.data(), &*s.end(), res); }
    static bool parse(const char *s, ::in_addr &res)
        { return parse(s, s + std::char_traits<char>::length(s), res); }
#endif
};
//////////////////////////////////////////////////////////////////////////////
class ipv6_addr : public ::in6_addr
{
    static __VIC_CONSTEXPR_FUNC uint8_t hi(uint16_t v) { return v >> 8; }
    static __VIC_CONSTEXPR_FUNC uint8_t lo(uint16_t v) { return v & 0xFFU; }
public:
    ipv6_addr() __VIC_DEFAULT_CTR
    __VIC_CONSTEXPR_FUNC ipv6_addr(::in6_addr a) : in6_addr(a) {}
    __VIC_CONSTEXPR_FUNC ipv6_addr(uint8_t a, uint8_t b, uint8_t c, uint8_t d,
                                   uint8_t e, uint8_t f, uint8_t g, uint8_t h,
                                   uint8_t i, uint8_t j, uint8_t k, uint8_t l,
                                   uint8_t m, uint8_t n, uint8_t o, uint8_t p)
#if __cpp_constexpr
        : in6_addr{{{a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p}}} {}
#else
        {
            uint8_t (&s)[16] = this->s6_addr;
            s[ 0] = a; s[ 1] = b; s[ 2] = c; s[ 3] = d; s[ 4] = e; s[ 5] = f;
            s[ 6] = g; s[ 7] = h; s[ 8] = i; s[ 9] = j; s[10] = k; s[11] = l;
            s[12] = m; s[13] = n; s[14] = o; s[15] = p;
        }
#endif

    __VIC_CONSTEXPR_FUNC ipv6_addr(uint16_t a, uint16_t b, uint16_t c, uint16_t d,
                                   uint16_t e, uint16_t f, uint16_t g, uint16_t h)
#if __cpp_constexpr
        :
#else
        { *this =
#endif
          ipv6_addr(hi(a),lo(a), hi(b),lo(b), hi(c),lo(c), hi(d),lo(d),
                    hi(e),lo(e), hi(f),lo(f), hi(g),lo(g), hi(h),lo(h))
#if __cpp_constexpr
        {}
#else
        ; }
#endif

    // IPv4-mapped IPv6 address
    explicit ipv6_addr(const ::in_addr &a)
#if __cpp_constexpr
        : in6_addr{}
#endif
    {
#if !__cpp_constexpr
        std::memset(&this->s6_addr, 0, 10);
#endif
        this->s6_addr[10] = this->s6_addr[11] = 0xFF;
        std::memcpy(this->s6_addr + 12, &a.s_addr, 4);
    }

    static __VIC_CONSTEXPR_FUNC ipv6_addr any() { return ipv6_addr(0,0,0,0,0,0,0,0); }
    static __VIC_CONSTEXPR_FUNC ipv6_addr loopback() { return ipv6_addr(0,0,0,0,0,0,0,1); }

    bool is_any() const
    {
        return load_unaligned<uint64_t>(this->s6_addr    ) == 0
            && load_unaligned<uint64_t>(this->s6_addr + 8) == 0;
    }
    bool is_loopback() const
    {
        int i = 0;
        for(; i < 15; i++)
            if(this->s6_addr[i]) return false;
        return this->s6_addr[i] == 1;
    }
    bool is_ipv4_mapped() const
    {
        //return IN6_IS_ADDR_V4MAPPED(this);
        uint64_t n64 = load_unaligned<uint64_t>(this->s6_addr);
        uint32_t n32 = load_unaligned<uint32_t>(this->s6_addr + 8);
        return n64 == 0 && n32 ==
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ // 0 == 0 if undefined (Windows)
            0xFFFF0000;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
            0x0000FFFF;
#endif
    }
    ipv4_addr to_ipv4() const
    {
        return ipv4_addr(this->s6_addr[12], this->s6_addr[13],
                         this->s6_addr[14], this->s6_addr[15]);
    }

    static bool parse(const char * , const char * , ::in6_addr & );
#if __cpp_lib_string_view
    static bool parse(std::string_view s, ::in6_addr &res)
        { return parse(s.data(), s.data() + s.length(), res); }
#else
    static bool parse(const std::string &s, ::in6_addr &res)
        { return parse(s.data(), &*s.end(), res); }
    static bool parse(const char *s, ::in6_addr &res)
        { return parse(s, s + std::char_traits<char>::length(s), res); }
#endif
};
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
#define __VIC_DEFINE_OP(OP,A1,A2) \
    __VIC_CONSTEXPR_FUNC bool operator OP(A1 a1, A2 a2) { return a1.s_addr OP a2.s_addr; }

__VIC_DEFINE_OP(==, ipv4_addr, ipv4_addr)
__VIC_DEFINE_OP(!=, ipv4_addr, ipv4_addr)
// Ordering depends on byte order but suitable for std::map etc
__VIC_DEFINE_OP(<=, ipv4_addr, ipv4_addr)
__VIC_DEFINE_OP(>=, ipv4_addr, ipv4_addr)
__VIC_DEFINE_OP(< , ipv4_addr, ipv4_addr)
__VIC_DEFINE_OP(> , ipv4_addr, ipv4_addr)

__VIC_DEFINE_OP(==, ipv4_addr, ::in_addr)
__VIC_DEFINE_OP(!=, ipv4_addr, ::in_addr)
__VIC_DEFINE_OP(<=, ipv4_addr, ::in_addr)
__VIC_DEFINE_OP(>=, ipv4_addr, ::in_addr)
__VIC_DEFINE_OP(< , ipv4_addr, ::in_addr)
__VIC_DEFINE_OP(> , ipv4_addr, ::in_addr)

__VIC_DEFINE_OP(==, ::in_addr, ipv4_addr)
__VIC_DEFINE_OP(!=, ::in_addr, ipv4_addr)
__VIC_DEFINE_OP(<=, ::in_addr, ipv4_addr)
__VIC_DEFINE_OP(>=, ::in_addr, ipv4_addr)
__VIC_DEFINE_OP(< , ::in_addr, ipv4_addr)
__VIC_DEFINE_OP(> , ::in_addr, ipv4_addr)

#undef __VIC_DEFINE_OP
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC ipv4_addr operator&(ipv4_addr a1, ipv4_addr a2)
{
    return ipv4_addr(a1.s_addr & a2.s_addr);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC int compare(const ::in6_addr &a1, const ::in6_addr &a2)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUILTINS)
    return __builtin_memcmp(a1.s6_addr, a2.s6_addr, 16);
#elif __cpp_constexpr >= 201304
    const uint8_t *p1 = a1.s6_addr, *p2 = a2.s6_addr;
    for(int c = 16; c--; p1++, p2++)
    {
        auto b1 = *p1, b2 = *p2;
        if(b1 < b2) return -1;
        if(b1 > b2) return  1;
    }
    return 0;
#else // C++11
    return
        a1.s6_addr[0]  < a2.s6_addr[0]  ? -1 : a1.s6_addr[0]  > a2.s6_addr[0]  ? 1 :
        a1.s6_addr[1]  < a2.s6_addr[1]  ? -1 : a1.s6_addr[1]  > a2.s6_addr[1]  ? 1 :
        a1.s6_addr[2]  < a2.s6_addr[2]  ? -1 : a1.s6_addr[2]  > a2.s6_addr[2]  ? 1 :
        a1.s6_addr[3]  < a2.s6_addr[3]  ? -1 : a1.s6_addr[3]  > a2.s6_addr[3]  ? 1 :
        a1.s6_addr[4]  < a2.s6_addr[4]  ? -1 : a1.s6_addr[4]  > a2.s6_addr[4]  ? 1 :
        a1.s6_addr[5]  < a2.s6_addr[5]  ? -1 : a1.s6_addr[5]  > a2.s6_addr[5]  ? 1 :
        a1.s6_addr[6]  < a2.s6_addr[6]  ? -1 : a1.s6_addr[6]  > a2.s6_addr[6]  ? 1 :
        a1.s6_addr[7]  < a2.s6_addr[7]  ? -1 : a1.s6_addr[7]  > a2.s6_addr[7]  ? 1 :
        a1.s6_addr[8]  < a2.s6_addr[8]  ? -1 : a1.s6_addr[8]  > a2.s6_addr[8]  ? 1 :
        a1.s6_addr[9]  < a2.s6_addr[9]  ? -1 : a1.s6_addr[9]  > a2.s6_addr[9]  ? 1 :
        a1.s6_addr[10] < a2.s6_addr[10] ? -1 : a1.s6_addr[10] > a2.s6_addr[10] ? 1 :
        a1.s6_addr[11] < a2.s6_addr[11] ? -1 : a1.s6_addr[11] > a2.s6_addr[11] ? 1 :
        a1.s6_addr[12] < a2.s6_addr[12] ? -1 : a1.s6_addr[12] > a2.s6_addr[12] ? 1 :
        a1.s6_addr[13] < a2.s6_addr[13] ? -1 : a1.s6_addr[13] > a2.s6_addr[13] ? 1 :
        a1.s6_addr[14] < a2.s6_addr[14] ? -1 : a1.s6_addr[14] > a2.s6_addr[14] ? 1 :
        a1.s6_addr[15] < a2.s6_addr[15] ? -1 : a1.s6_addr[15] > a2.s6_addr[15] ? 1 :
        0;
#endif
}
//----------------------------------------------------------------------------
#define __VIC_DEFINE_OP(OP,A1,A2) \
    __VIC_CONSTEXPR_FUNC bool operator OP(const A1 &a1, const A2 &a2) { return compare(a1, a2) OP 0; }

__VIC_DEFINE_OP(==, ipv6_addr, ipv6_addr)
__VIC_DEFINE_OP(!=, ipv6_addr, ipv6_addr)
__VIC_DEFINE_OP(<=, ipv6_addr, ipv6_addr)
__VIC_DEFINE_OP(>=, ipv6_addr, ipv6_addr)
__VIC_DEFINE_OP(< , ipv6_addr, ipv6_addr)
__VIC_DEFINE_OP(> , ipv6_addr, ipv6_addr)

__VIC_DEFINE_OP(==, ipv6_addr, ::in6_addr)
__VIC_DEFINE_OP(!=, ipv6_addr, ::in6_addr)
__VIC_DEFINE_OP(<=, ipv6_addr, ::in6_addr)
__VIC_DEFINE_OP(>=, ipv6_addr, ::in6_addr)
__VIC_DEFINE_OP(< , ipv6_addr, ::in6_addr)
__VIC_DEFINE_OP(> , ipv6_addr, ::in6_addr)

__VIC_DEFINE_OP(==, ::in6_addr, ipv6_addr)
__VIC_DEFINE_OP(!=, ::in6_addr, ipv6_addr)
__VIC_DEFINE_OP(<=, ::in6_addr, ipv6_addr)
__VIC_DEFINE_OP(>=, ::in6_addr, ipv6_addr)
__VIC_DEFINE_OP(< , ::in6_addr, ipv6_addr)
__VIC_DEFINE_OP(> , ::in6_addr, ipv6_addr)

#undef __VIC_DEFINE_OP
//----------------------------------------------------------------------------
inline ipv6_addr operator&(ipv6_addr a1, const ipv6_addr &a2)
{
    uint8_t *p1 = a1.s6_addr;
    const uint8_t *p2 = a2.s6_addr;
    for(int i = 16; i > 0; i--) *p1++ &= *p2++;
    return a1;
}
//----------------------------------------------------------------------------

void to_text_append(::in_addr , std::string & );
void to_text_append(const ::in6_addr & , std::string & );

} // namespace

#if __cplusplus >= 201103L // C++11
namespace std {
//////////////////////////////////////////////////////////////////////////////
template<> struct hash< ::__vic::ipv4_addr>
{
    std::size_t operator()(const ::__vic::ipv4_addr &v) const
    { return std::hash< ::__vic::in_addr_t>{}(v.s_addr); }
};
//////////////////////////////////////////////////////////////////////////////
template<> struct hash< ::__vic::ipv6_addr>
{
private:
    static uint64_t to_uint64(const uint8_t *p)
    {
        // NOTE: byte-order dependent
        return ::__vic::load_unaligned<uint64_t>(p);
    }
public:
    std::size_t operator()(const ::__vic::ipv6_addr &v) const
    { return std::hash<uint64_t>{}(
        to_uint64(v.s6_addr) + to_uint64(v.s6_addr + 8)); }
};
//////////////////////////////////////////////////////////////////////////////
} // namespace
#endif // C++11

#endif // header guard
