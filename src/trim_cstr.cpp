//
// $Id$
//

#include<__vic/string_utils.h>
#include<__vic/tchar.h>
#include<__vic/char_predicates.h>
#include<cstring>

namespace __vic {

namespace {

//----------------------------------------------------------------------------
template<class charT, class Pred>
inline void trim_if_back(charT *st, Pred pred)
{
    charT *last = tchar::end(st) - 1;
    charT *p = last;
    while(p >= st && pred(*p)) p--;
    if(p != last) *(++p) = charT();
}
//----------------------------------------------------------------------------
template<class charT, class Pred>
inline void trim_if_front(charT *st, Pred pred)
{
    charT *p = st;
    while(*p && pred(*p)) p++;
    if(p != st) tchar::move(st, p);
}
//----------------------------------------------------------------------------
template<class charT, class Pred>
inline void trim_if(charT *st, Pred pred)
{
    charT *last = tchar::end(st) - 1;
    // trim back
    charT *p = last;
    while(p >= st && pred(*p)) p--;
    if(p != last)
    {
        last = p;
        *(++p) = charT();
    }
    // trim front
    p = st;
    while(p <= last && pred(*p)) p++;
    if(p != st) std::memmove(st, p, (last - p + 2) * sizeof(charT));
}
//----------------------------------------------------------------------------

} // namespace

//----------------------------------------------------------------------------
char *trim(char *st) noexcept
{
    if(st) trim_if(st, is_ascii_ws());
    return st;
}
//----------------------------------------------------------------------------
char *trim_back(char *st) noexcept
{
    if(st) trim_if_back(st, is_ascii_ws());
    return st;
}
//----------------------------------------------------------------------------
char *trim_front(char *st) noexcept
{
    if(st) trim_if_front(st, is_ascii_ws());
    return st;
}
//----------------------------------------------------------------------------
char *trim(char *st, char ch) noexcept
{
    if(st) trim_if(st, is_eq_char(ch));
    return st;
}
//----------------------------------------------------------------------------
char *trim_back(char *st, char ch) noexcept
{
    if(st) trim_if_back(st, is_eq_char(ch));
    return st;
}
//----------------------------------------------------------------------------
char *trim_front(char *st, char ch) noexcept
{
    if(st) trim_if_front(st, is_eq_char(ch));
    return st;
}
//----------------------------------------------------------------------------
char *trim(char *st, const char *set) noexcept
{
    if(st && set) trim_if(st, is_one_of_chars(set));
    return st;
}
//----------------------------------------------------------------------------
char *trim_back(char *st, const char *set) noexcept
{
    if(st && set) trim_if_back(st, is_one_of_chars(set));
    return st;
}
//----------------------------------------------------------------------------
char *trim_front(char *st, const char *set) noexcept
{
    if(st && set) trim_if_front(st, is_one_of_chars(set));
    return st;
}
//----------------------------------------------------------------------------

} // namespace
