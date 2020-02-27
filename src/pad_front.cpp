//
// $Id$
//

#include<__vic/string_utils.h>
#include<cstring>

namespace __vic {

//----------------------------------------------------------------------------
char *pad_front(char *st, size_t size, char pad_ch)
{
    if(!st) return st;
    size_t sz = std::strlen(st);
    if(sz < size)
    {
        size_t n = size - sz;
        std::memmove(st + n, st, sz + 1);
        std::memset(st, pad_ch, n);
    }
    return st;
}
//----------------------------------------------------------------------------

} // namespace
