//
// $Id$
//

#include<__vic/to_text.h>
#include<cstdio>

namespace __vic {

//----------------------------------------------------------------------------
template<size_t Size, class T>
inline size_t __vic_snprintf(char (&buf)[Size], const char *fmt, T v)
{
#if __cplusplus >= 201103L
    return std::snprintf(buf, Size, fmt, v);
#else
    return std::sprintf(buf, fmt, v);
#endif
}
//----------------------------------------------------------------------------
void to_text_append(long n, std::string &s)
{
    char buf[sizeof n <= 8 ? 32 : -1]; // static_assert(sizeof n <= 8)
    size_t len = __vic_snprintf(buf, "%ld", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------
void to_text_append(unsigned long n, std::string &s)
{
    char buf[sizeof n <= 8 ? 32 : -1]; // static_assert(sizeof n <= 8)
    size_t len = __vic_snprintf(buf, "%lu", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------
void to_text_append(__VIC_LONGLONG n, std::string &s)
{
    char buf[sizeof n <= 8 ? 32 : -1]; // static_assert(sizeof n <= 8)
    size_t len = __vic_snprintf(buf, "%" __VIC_PRINTF_ll "d", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------
void to_text_append(unsigned __VIC_LONGLONG n, std::string &s)
{
    char buf[sizeof n <= 8 ? 32 : -1]; // static_assert(sizeof n <= 8)
    size_t len = __vic_snprintf(buf, "%" __VIC_PRINTF_ll "u", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------
void to_text_append(double n, std::string &s)
{
    char buf[sizeof n <= 16 ? 32 : -1]; // static_assert(sizeof n <= 16)
    size_t len = __vic_snprintf(buf, "%G", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------
void to_text_append(long double n, std::string &s)
{
    char buf[sizeof n <= 16 ? 32 : -1]; // static_assert(sizeof n <= 16)
    size_t len = __vic_snprintf(buf, "%LG", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------
void to_text_append(const void *p, std::string &s)
{
    char buf[sizeof p <= 8 ? 32 : -1]; // static_assert(sizeof p <= 8)
    size_t len = __vic_snprintf(buf, "%p", p);
    s.append(buf, len);
}
//----------------------------------------------------------------------------

} // namespace
