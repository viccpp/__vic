//
// $Id$
//

#include<__vic/ascii_string.h>
#include<__vic/ascii.h>

namespace __vic { namespace ascii {

//----------------------------------------------------------------------------
bool equal_icase(const char *s1, const char *s2)
{
    while(*s1 && *s2)
        if(!equal_icase(*s1++, *s2++)) return false;
    return !*s1 && !*s2;
}
//----------------------------------------------------------------------------
bool equal_icase(const char *s1, size_t s1_len,
                 const char *s2, size_t s2_len)
{
    if(s1_len != s2_len) return false;
    while(s1_len--)
        if(!equal_icase(*s1++, *s2++)) return false;
    return true;
}
//----------------------------------------------------------------------------

}} // namespace
