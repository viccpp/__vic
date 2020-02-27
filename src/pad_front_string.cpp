//
// $Id$
//

#include<__vic/string_utils.h>

namespace __vic {

//----------------------------------------------------------------------------
std::string &pad_front(std::string &st, size_t size, char pad_ch)
{
    if(st.length() < size) st.insert(0, size - st.length(), pad_ch);
    return st;
}
//----------------------------------------------------------------------------

} // namespace
