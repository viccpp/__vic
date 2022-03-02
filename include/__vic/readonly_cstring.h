// The simple non-mutable null-terminated string class
// with automatic memory management
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_READONLY_CSTRING_H
#define __VIC_READONLY_CSTRING_H

#include<__vic/defs.h>
#include __VIC_SWAP_HEADER
#include<cstring>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class readonly_cstring
{
    const char *st;
    static const char empty_str[1];
    static const char *nonnull(const char *s) { return s ? s : empty_str; }
    static const char *dup(const char * , size_t = size_t(-1));
public:
    __VIC_CONSTEXPR_FUNC readonly_cstring() : st(nullptr) {}
    readonly_cstring(const char *s) : st(dup(s)) {}
    readonly_cstring(const char *begin, const char *end) : st(dup(begin, end-begin)) {}
    readonly_cstring(const char *s, size_t n) : st(dup(s, n)) {}
    readonly_cstring(const readonly_cstring &s) : st(dup(s.st)) {}
    ~readonly_cstring() noexcept; // for error.h

    readonly_cstring &operator=(const char * );
    readonly_cstring &operator=(const readonly_cstring & );
    readonly_cstring &assign(const char * , const char * );
    readonly_cstring &assign(const char * , size_t );

#if __cpp_rvalue_references
    readonly_cstring(readonly_cstring &&s) noexcept : st(s.st) { s.st = nullptr; }
    readonly_cstring &operator=(readonly_cstring &&s) noexcept
        { swap(s); return *this; }
#endif

    // allocates internal buffer and returns pointer to it. Use with care!
    // specified size must include space for '\0' terminator!
    char *reserve(size_t );

    friend int compare(const readonly_cstring &s1, const readonly_cstring &s2)
    {
        return std::strcmp(s1, s2);
    }
    friend int compare(const readonly_cstring &s1, const char *s2)
    {
        return std::strcmp(s1, nonnull(s2));
    }
    friend int compare(const char *s1, const readonly_cstring &s2)
    {
        return std::strcmp(nonnull(s1), s2);
    }

    bool empty() const { return !st || *st == '\0'; }
    const char *c_str() const { return nonnull(st); }
    operator const char*() const { return c_str(); }

    void swap(readonly_cstring &s) noexcept { std::swap(st, s.st); }
};
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// readonly_cstring compare operators
//----------------------------------------------------------------------------
#define __VIC_DEFINE_OP(OP,T1,T2) \
    inline bool operator OP(T1 s1, T2 s2) { return compare(s1, s2) OP 0; }

__VIC_DEFINE_OP(==, const readonly_cstring &, const readonly_cstring &)
__VIC_DEFINE_OP(!=, const readonly_cstring &, const readonly_cstring &)
__VIC_DEFINE_OP(< , const readonly_cstring &, const readonly_cstring &)
__VIC_DEFINE_OP(> , const readonly_cstring &, const readonly_cstring &)
__VIC_DEFINE_OP(<=, const readonly_cstring &, const readonly_cstring &)
__VIC_DEFINE_OP(>=, const readonly_cstring &, const readonly_cstring &)

__VIC_DEFINE_OP(==, const readonly_cstring &, const char *)
__VIC_DEFINE_OP(!=, const readonly_cstring &, const char *)
__VIC_DEFINE_OP(< , const readonly_cstring &, const char *)
__VIC_DEFINE_OP(> , const readonly_cstring &, const char *)
__VIC_DEFINE_OP(<=, const readonly_cstring &, const char *)
__VIC_DEFINE_OP(>=, const readonly_cstring &, const char *)

__VIC_DEFINE_OP(==, const char *, const readonly_cstring &)
__VIC_DEFINE_OP(!=, const char *, const readonly_cstring &)
__VIC_DEFINE_OP(< , const char *, const readonly_cstring &)
__VIC_DEFINE_OP(> , const char *, const readonly_cstring &)
__VIC_DEFINE_OP(<=, const char *, const readonly_cstring &)
__VIC_DEFINE_OP(>=, const char *, const readonly_cstring &)

#undef __VIC_DEFINE_OP
//----------------------------------------------------------------------------
inline void swap(readonly_cstring &s1, readonly_cstring &s2) noexcept
{
    s1.swap(s2);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
