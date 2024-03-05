//
// $Id$
//

#include<__vic/readonly_cstring.h>
#include<cstring>

namespace __vic {

const char readonly_cstring::empty_str[1] = { '\x0' };
//----------------------------------------------------------------------------
readonly_cstring::~readonly_cstring() noexcept
{
    delete [] st;
}
//----------------------------------------------------------------------------
char *readonly_cstring::reserve(size_t n)
{
    char *p = new char[n];
    *p = '\x0'; // empty string
    delete [] st;
    st = p;
    return p;
}
//----------------------------------------------------------------------------
readonly_cstring &readonly_cstring::assign(const char *s, size_t n)
{
    const char *p = dup(s, n);
    delete [] st;
    st = p;
    return *this;
}
//----------------------------------------------------------------------------
const char *readonly_cstring::dup(const char *s, size_t n)
{
    if(!s || n==0) return nullptr;
    if(n == size_t(-1)) n = std::strlen(s);
    char *st = new char[n+1];
    std::memcpy(st, s, n);
    st[n] = '\x0';
    return st;
}
//----------------------------------------------------------------------------

} // namespace
