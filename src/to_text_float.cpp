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
    size_t len = std::snprintf(buf, Size, fmt, v);;
    return len < Size ? len : Size-1U;
#else
    return std::sprintf(buf, fmt, v);
#endif
}
//----------------------------------------------------------------------------
void to_text_append(double n, std::string &s)
{
    char buf[sizeof n <= 16 ? 64 : -1]; // static_assert(sizeof n <= 16)
    size_t len = __vic_snprintf(buf, "%G", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------
void to_text_append(long double n, std::string &s)
{
    char buf[sizeof n <= 16 ? 64 : -1]; // static_assert(sizeof n <= 16)
    size_t len = __vic_snprintf(buf, "%LG", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------

} // namespace
