//
// $Id$
//

#include<__vic/string_utils.h>
#include<string>

namespace __vic {

//----------------------------------------------------------------------------
bool ends_with(const char *s, size_t s_len, const char *suff, size_t suff_len)
{
    if(s_len < suff_len) return false;
    return std::string::traits_type::compare(
        s + (s_len - suff_len), suff, suff_len) == 0;
}
//----------------------------------------------------------------------------

} // namespace
