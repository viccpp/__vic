// The simple static string class
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_STATIC_STRING_H
#define __VIC_STATIC_STRING_H

#include<__vic/defs.h>
#include __VIC_SWAP_HEADER
#include<cstring>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Simple, safe and lightweight implementation of non-mutable string
class static_string
{
    const char *st;
    static const char *dup(const char * , size_t = size_t(-1));
public:
    __VIC_CONSTEXPR_FUNC static_string() : st(nullptr) {}
    static_string(const char *s) : st(dup(s)) {}
    static_string(const char *begin, const char *end) : st(dup(begin, end-begin)) {}
    static_string(const char *s, size_t n) : st(dup(s, n)) {}
    static_string(const static_string &s) : st(dup(s.st)) {}
    ~static_string() noexcept; // for error.h

    static_string &operator=(const char * );
    static_string &operator=(const static_string & );
    static_string &assign(const char * , const char * );
    static_string &assign(const char * , size_t );

#if __cpp_rvalue_references
    static_string(static_string &&s) noexcept : st(s.st) { s.st = nullptr; }
    static_string &operator=(static_string &&s) noexcept
        { swap(s); return *this; }
#endif

    // allocates internal buffer and returns pointer to it. Use with care!
    // specified size must include space for '\0' terminator!
    char *reserve(size_t );

    int compare(const char *s) const { return std::strcmp(*this, s ? s : ""); }
    bool empty() const { return !st || *st == '\0'; }
    const char *c_str() const { return st ? st : ""; }
    operator const char*() const { return c_str(); }

    void swap(static_string &s) noexcept { std::swap(st, s.st); }
};
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// static_string compare function and operators
//----------------------------------------------------------------------------
inline int compare(const static_string &s1, const static_string &s2)
{
    return std::strcmp(s1, s2);
}
inline int compare(const static_string &s1, const char *s2)
{
    return s1.compare(s2);
}
inline int compare(const char *s1, const static_string &s2)
{
    return s2.compare(s1);
}
//----------------------------------------------------------------------------
#define __VIC_DEFINE_OP(OP,T1,T2) \
    inline bool operator OP(T1 s1, T2 s2) { return compare(s1, s2) OP 0; }

__VIC_DEFINE_OP(==, const static_string &, const static_string &)
__VIC_DEFINE_OP(!=, const static_string &, const static_string &)
__VIC_DEFINE_OP(< , const static_string &, const static_string &)
__VIC_DEFINE_OP(> , const static_string &, const static_string &)
__VIC_DEFINE_OP(<=, const static_string &, const static_string &)
__VIC_DEFINE_OP(>=, const static_string &, const static_string &)

__VIC_DEFINE_OP(==, const static_string &, const char *)
__VIC_DEFINE_OP(!=, const static_string &, const char *)
__VIC_DEFINE_OP(< , const static_string &, const char *)
__VIC_DEFINE_OP(> , const static_string &, const char *)
__VIC_DEFINE_OP(<=, const static_string &, const char *)
__VIC_DEFINE_OP(>=, const static_string &, const char *)

__VIC_DEFINE_OP(==, const char *, const static_string &)
__VIC_DEFINE_OP(!=, const char *, const static_string &)
__VIC_DEFINE_OP(< , const char *, const static_string &)
__VIC_DEFINE_OP(> , const char *, const static_string &)
__VIC_DEFINE_OP(<=, const char *, const static_string &)
__VIC_DEFINE_OP(>=, const char *, const static_string &)

#undef __VIC_DEFINE_OP
//----------------------------------------------------------------------------
inline void swap(static_string &s1, static_string &s2) noexcept { s1.swap(s2); }
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
