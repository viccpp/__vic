//
// $Id$
//

#include<__vic/string_ops.h>

namespace __vic {

//----------------------------------------------------------------------------
std::string &pad_left(std::string &st, size_t size, char pad_ch)
{
    if(st.length() < size) st.insert(0, size - st.length(), pad_ch);
    return st;
}
//----------------------------------------------------------------------------

} // namespace
