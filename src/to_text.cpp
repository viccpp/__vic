//
// $Id$
//

#include<__vic/to_text.h>
#include<cstdio>

namespace __vic {

//----------------------------------------------------------------------------
void to_text_append(long n, std::string &s)
{
    char buf[16];
    size_t len = std::sprintf(buf, "%ld", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------
void to_text_append(unsigned long n, std::string &s)
{
    char buf[16];
    size_t len = std::sprintf(buf, "%lu", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------
void to_text_append(__VIC_LONGLONG n, std::string &s)
{
    char buf[32];
    size_t len = std::sprintf(buf, "%lld", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------
void to_text_append(unsigned __VIC_LONGLONG n, std::string &s)
{
    char buf[32];
    size_t len = std::sprintf(buf, "%llu", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------
void to_text_append(double n, std::string &s)
{
    char buf[32];
    size_t len = std::sprintf(buf, "%G", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------
void to_text_append(long double n, std::string &s)
{
    char buf[32];
    size_t len = std::sprintf(buf, "%LG", n);
    s.append(buf, len);
}
//----------------------------------------------------------------------------
void to_text_append(const void *p, std::string &s)
{
    char buf[32];
    size_t len = std::sprintf(buf, "%p", p);
    s.append(buf, len);
}
//----------------------------------------------------------------------------

} // namespace
