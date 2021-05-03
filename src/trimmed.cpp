//
// $Id$
//

#include<__vic/string_utils.h>
#include<__vic/algorithm.h>
#include<__vic/char_predicates.h>

namespace __vic {

namespace {

//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc, class Pred>
inline std::basic_string<charT,Traits,Alloc> trimmed_if_back(
    const std::basic_string<charT,Traits,Alloc> &st, Pred pred)
{
    const charT *begin = st.data();
    return std::basic_string<charT,Traits,Alloc>(
        begin, skip_if_back(begin, &*st.end(), pred));
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc, class Pred>
inline std::basic_string<charT,Traits,Alloc> trimmed_if_front(
    const std::basic_string<charT,Traits,Alloc> &st, Pred pred)
{
    const charT *end = &*st.end();
    return std::basic_string<charT,Traits,Alloc>(
        skip_if_front(st.data(), end, pred), end);
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc, class Pred>
inline std::basic_string<charT,Traits,Alloc> trimmed_if(
    const std::basic_string<charT,Traits,Alloc> &st, Pred pred)
{
    const charT *begin = st.data();
    const charT *e = skip_if_back(begin, &*st.end(), pred);
    const charT *b = skip_if_front(begin, e, pred);
    return std::basic_string<charT,Traits,Alloc>(b, e);
}
//----------------------------------------------------------------------------

} // namespace

//----------------------------------------------------------------------------
std::string trimmed(const std::string &st)
{
    return trimmed_if(st, is_ascii_ws());
}
//----------------------------------------------------------------------------
std::string trimmed_back(const std::string &st)
{
    return trimmed_if_back(st, is_ascii_ws());
}
//----------------------------------------------------------------------------
std::string trimmed_front(const std::string &st)
{
    return trimmed_if_front(st, is_ascii_ws());
}
//----------------------------------------------------------------------------
std::string trimmed(const std::string &st, char ch)
{
    return trimmed_if(st, is_eq_char(ch));
}
//----------------------------------------------------------------------------
std::string trimmed_back(const std::string &st, char ch)
{
    return trimmed_if_back(st, is_eq_char(ch));
}
//----------------------------------------------------------------------------
std::string trimmed_front(const std::string &st, char ch)
{
    return trimmed_if_front(st, is_eq_char(ch));
}
//----------------------------------------------------------------------------
std::string trimmed(const std::string &st, const char *set)
{
    return set ? trimmed_if(st, is_one_of_chars(set)) : st;
}
//----------------------------------------------------------------------------
std::string trimmed_back(const std::string &st, const char *set)
{
    return set ? trimmed_if_back(st, is_one_of_chars(set)) : st;
}
//----------------------------------------------------------------------------
std::string trimmed_front(const std::string &st, const char *set)
{
    return set ? trimmed_if_front(st, is_one_of_chars(set)) : st;
}
//----------------------------------------------------------------------------

} // namespace
