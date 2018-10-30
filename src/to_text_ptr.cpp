//
// $Id$
//

#include<__vic/to_text.h>
#include<cstdio>

namespace __vic {

//----------------------------------------------------------------------------
void to_text_append(const void *p, std::string &s)
{
    char buf[sizeof p <= 8 ? 32 : -1]; // static_assert(sizeof p <= 8)
    size_t len =
#if __cplusplus >= 201103L
    std::snprintf(buf, sizeof buf, "%p", p);
    if(len >= sizeof buf) len = sizeof buf - 1;
#else
    std::sprintf(buf, "%p", p);
#endif
    s.append(buf, len);
}
//----------------------------------------------------------------------------

} // namespace
