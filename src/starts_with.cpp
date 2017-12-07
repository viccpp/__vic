//
// $Id$
//

#include<__vic/string_utils.h>
#include<string>

namespace __vic {

//----------------------------------------------------------------------------
bool starts_with(const char *s, size_t s_len, const char *pref)
{
    for(; *pref; ++pref, ++s)
        if(s_len-- == 0 || *s != *pref) return false;
    return true;
}
//----------------------------------------------------------------------------
bool starts_with(const char *s, size_t s_len, const char *pref, size_t pref_len)
{
    if(s_len < pref_len) return false;
    return std::string::traits_type::compare(s, pref, pref_len) == 0;
}
//----------------------------------------------------------------------------
bool starts_with(const char *s, const char *pref)
{
    for(; *pref; ++pref, ++s)
        if(!*s || *s != *pref) return false;
    return true;
}
//----------------------------------------------------------------------------
bool starts_with(const char *s, const char *pref, size_t pref_len)
{
    for(; pref_len--; ++pref, ++s)
        if(!*s || *s != *pref) return false;
    return true;
}
//----------------------------------------------------------------------------

} // namespace
