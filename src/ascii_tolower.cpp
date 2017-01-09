//
// $Id$
//

#include<__vic/ascii_string.h>
#include<__vic/ascii.h>

namespace __vic { namespace ascii {

//----------------------------------------------------------------------------
char *tolower(char *st)
{
    for(char *p = st; *p; p++)
    {
        const char ch = *p;
        if(isupper(ch)) *p = upper_to_lower(ch);
    }
    return st;
}
//----------------------------------------------------------------------------

}} // namespace
