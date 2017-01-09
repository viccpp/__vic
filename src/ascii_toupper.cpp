//
// $Id$
//

#include<__vic/ascii_string.h>
#include<__vic/ascii.h>

namespace __vic { namespace ascii {

//----------------------------------------------------------------------------
char *toupper(char *st)
{
    for(char *p = st; *p; p++)
    {
        const char ch = *p;
        if(islower(ch)) *p = lower_to_upper(ch);
    }
    return st;
}
//----------------------------------------------------------------------------

}} // namespace
