//
// $Id$
//

#include<__vic/ascii_string.h>
#include<__vic/ascii.h>

namespace __vic { namespace ascii {

//----------------------------------------------------------------------------
std::string &toupper(std::string &st)
{
    for(std::string::iterator it = st.begin(); it != st.end(); ++it)
    {
        const char ch = *it;
        if(islower(ch)) *it = lower_to_upper(ch);
    }
    return st;
}
//----------------------------------------------------------------------------

}} // namespace
