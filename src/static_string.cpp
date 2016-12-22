//
// $Id$
//

#include<__vic/static_string.h>
#include<cstring>

namespace __vic {

//----------------------------------------------------------------------------
static_string::~static_string() noexcept
{
    delete [] st;
}
//----------------------------------------------------------------------------
char *static_string::reserve(size_t n)
{
    char *p = new char[n];
    *p = '\x0'; // empty string
    delete [] st;
    st = p;
    return p;
}
//----------------------------------------------------------------------------
static_string &static_string::operator=(const char *s)
{
    const char *p = dup(s);
    delete [] st;
    st = p;
    return *this;
}
//----------------------------------------------------------------------------
static_string &static_string::operator=(const static_string &s)
{
    const char *p = dup(s.st);
    delete [] st;
    st = p;
    return *this;
}
//----------------------------------------------------------------------------
static_string &static_string::assign(const char *begin, const char *end)
{
    const char *p = dup(begin, end - begin);
    delete [] st;
    st = p;
    return *this;
}
//----------------------------------------------------------------------------
static_string &static_string::assign(const char *s, size_t n)
{
    const char *p = dup(s, n);
    delete [] st;
    st = p;
    return *this;
}
//----------------------------------------------------------------------------
const char *static_string::dup(const char *s, size_t n)
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
