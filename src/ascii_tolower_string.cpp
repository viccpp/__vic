//
// $Id$
//

#include<__vic/ascii_string.h>
#include<__vic/ascii.h>

namespace __vic { namespace ascii {

//----------------------------------------------------------------------------
std::string &tolower(std::string &st)
{
    for(std::string::iterator it = st.begin(); it != st.end(); ++it)
    {
        const char ch = *it;
        if(isupper(ch)) *it = upper_to_lower(ch);
    }
    return st;
}
//----------------------------------------------------------------------------

}} // namespace
