//
// $Id$
//

#include<__vic/string_utils.h>
#include<cstring>

namespace __vic {

//----------------------------------------------------------------------------
char *pad_right(char *st, size_t size, char pad_ch)
{
    if(!st) return st;
    size_t sz = std::strlen(st);
    if(sz < size)
    {
        std::memset(st + sz, pad_ch, size - sz);
        st[size] = '\0';
    }
    return st;
}
//----------------------------------------------------------------------------

} // namespace
