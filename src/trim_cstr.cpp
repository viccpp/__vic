//
// $Id$
//

#include<__vic/string_utils.h>
#include<__vic/algorithm.h>
#include<__vic/tchar.h>
#include<__vic/char_predicates.h>
#include<cstring>

namespace __vic {

namespace {

//----------------------------------------------------------------------------
template<class charT, class Pred>
inline void trim_back_if(charT *st, Pred pred)
{
    charT *end = tchar::end(st);
    charT *p = skip_back_if(st, end, pred);
    if(p != end) *p = charT();
}
//----------------------------------------------------------------------------
template<class charT, class Pred>
inline void trim_front_if(charT *st, Pred pred)
{
    charT *p = st;
    while(*p && pred(*p)) p++;
    if(p != st) tchar::move(st, p);
}
//----------------------------------------------------------------------------
template<class charT, class Pred>
inline void trim_if(charT *st, Pred pred)
{
    charT *end = tchar::end(st);
    // trim back
    charT *e = skip_back_if(st, end, pred);
    if(e != end) *e = charT();
    // trim front
    charT *b = skip_front_if(st, e, pred);
    if(b != st) std::memmove(st, b, (e - b + 1) * sizeof(charT));
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
    if(st) trim_back_if(st, is_ascii_ws());
    return st;
}
//----------------------------------------------------------------------------
char *trim_front(char *st) noexcept
{
    if(st) trim_front_if(st, is_ascii_ws());
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
    if(st) trim_back_if(st, is_eq_char(ch));
    return st;
}
//----------------------------------------------------------------------------
char *trim_front(char *st, char ch) noexcept
{
    if(st) trim_front_if(st, is_eq_char(ch));
    return st;
}
//----------------------------------------------------------------------------
char *trim(char *st, const set_of_chars &set) noexcept
{
    if(st) trim_if(st, is_one_of_chars(set));
    return st;
}
//----------------------------------------------------------------------------
char *trim_back(char *st, const set_of_chars &set) noexcept
{
    if(st) trim_back_if(st, is_one_of_chars(set));
    return st;
}
//----------------------------------------------------------------------------
char *trim_front(char *st, const set_of_chars &set) noexcept
{
    if(st) trim_front_if(st, is_one_of_chars(set));
    return st;
}
//----------------------------------------------------------------------------

} // namespace
