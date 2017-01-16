//
// $Id$
//

#include<__vic/string_ops.h>
#include<cstring>

namespace __vic {

//----------------------------------------------------------------------------
std::string &pad_right(std::string &st, size_t size, char pad_ch)
{
    if(st.length() < size) st.append(size - st.length(), pad_ch);
    return st;
}
//----------------------------------------------------------------------------

} // namespace
