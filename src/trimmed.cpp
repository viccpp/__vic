//
// $Id$
//

#include<__vic/string_utils.h>
#include<__vic/algorithm.h>
#include<__vic/char_predicates.h>

namespace __vic {

#if !__cpp_lib_string_view
namespace {

//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc, class Pred>
inline std::basic_string<charT,Traits,Alloc> trimmed_back_if(
    const std::basic_string<charT,Traits,Alloc> &st, Pred pred)
{
    const charT *begin = st.data();
    return std::basic_string<charT,Traits,Alloc>(
        begin, skip_back_if(begin, begin + st.length(), pred));
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc, class Pred>
inline std::basic_string<charT,Traits,Alloc> trimmed_front_if(
    const std::basic_string<charT,Traits,Alloc> &st, Pred pred)
{
    const charT *begin = st.data(),
                *end = begin + st.length();
    return std::basic_string<charT,Traits,Alloc>(
        skip_front_if(begin, end, pred), end);
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc, class Pred>
inline std::basic_string<charT,Traits,Alloc> trimmed_if(
    const std::basic_string<charT,Traits,Alloc> &st, Pred pred)
{
    const charT *begin = st.data(),
                *end = begin + st.length();
    const charT *e = skip_back_if(begin, end, pred);
    const charT *b = skip_front_if(begin, e, pred);
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
    return trimmed_back_if(st, is_ascii_ws());
}
//----------------------------------------------------------------------------
std::string trimmed_front(const std::string &st)
{
    return trimmed_front_if(st, is_ascii_ws());
}
//----------------------------------------------------------------------------
std::string trimmed(const std::string &st, char ch)
{
    return trimmed_if(st, is_eq_char(ch));
}
//----------------------------------------------------------------------------
std::string trimmed_back(const std::string &st, char ch)
{
    return trimmed_back_if(st, is_eq_char(ch));
}
//----------------------------------------------------------------------------
std::string trimmed_front(const std::string &st, char ch)
{
    return trimmed_front_if(st, is_eq_char(ch));
}
//----------------------------------------------------------------------------
std::string trimmed(const std::string &st, const set_of_chars &set)
{
    return trimmed_if(st, is_one_of_chars(&set));
}
//----------------------------------------------------------------------------
std::string trimmed_back(const std::string &st, const set_of_chars &set)
{
    return trimmed_back_if(st, is_one_of_chars(&set));
}
//----------------------------------------------------------------------------
std::string trimmed_front(const std::string &st, const set_of_chars &set)
{
    return trimmed_front_if(st, is_one_of_chars(&set));
}
//----------------------------------------------------------------------------
#endif

} // namespace
