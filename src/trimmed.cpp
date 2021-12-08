//
// $Id$
//

#include<__vic/string_utils.h>
#include<__vic/algorithm.h>
#include<__vic/char_predicates.h>

namespace __vic {

#if __cpp_lib_string_view // C++17
namespace {

//----------------------------------------------------------------------------
template<class charT, class Traits, class Pred>
inline std::basic_string_view<charT,Traits> trimmed_if_back(
    std::basic_string_view<charT,Traits> st, Pred pred)
{
    const charT *begin = st.data();
    const charT *end = skip_if_back(begin, begin + st.length(), pred);
    return {begin, static_cast<std::size_t>(end - begin)};
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Pred>
inline std::basic_string_view<charT,Traits> trimmed_if_front(
    std::basic_string_view<charT,Traits> st, Pred pred)
{
    const charT *begin = st.data();
    const charT *end = begin + st.length();
    begin = skip_if_front(begin, end, pred);
    return {begin, static_cast<std::size_t>(end - begin)};
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Pred>
inline std::basic_string_view<charT,Traits> trimmed_if(
    std::basic_string_view<charT,Traits> st, Pred pred)
{
    const charT *begin = st.data();
    const charT *end = begin + st.length();
    end = skip_if_back(begin, end, pred);
    begin = skip_if_front(begin, end, pred);
    return {begin, static_cast<std::size_t>(end - begin)};
}
//----------------------------------------------------------------------------

} // namespace

//----------------------------------------------------------------------------
std::string_view trimmed(std::string_view st)
{
    return trimmed_if(st, is_ascii_ws());
}
//----------------------------------------------------------------------------
std::string_view trimmed_back(std::string_view st)
{
    return trimmed_if_back(st, is_ascii_ws());
}
//----------------------------------------------------------------------------
std::string_view trimmed_front(std::string_view st)
{
    return trimmed_if_front(st, is_ascii_ws());
}
//----------------------------------------------------------------------------
std::string_view trimmed(std::string_view st, char ch)
{
    return trimmed_if(st, is_eq_char(ch));
}
//----------------------------------------------------------------------------
std::string_view trimmed_back(std::string_view st, char ch)
{
    return trimmed_if_back(st, is_eq_char(ch));
}
//----------------------------------------------------------------------------
std::string_view trimmed_front(std::string_view st, char ch)
{
    return trimmed_if_front(st, is_eq_char(ch));
}
//----------------------------------------------------------------------------
std::string_view trimmed(std::string_view st, const char *set)
{
    return set ? trimmed_if(st, is_one_of_chars(set)) : st;
}
//----------------------------------------------------------------------------
std::string_view trimmed_back(std::string_view st, const char *set)
{
    return set ? trimmed_if_back(st, is_one_of_chars(set)) : st;
}
//----------------------------------------------------------------------------
std::string_view trimmed_front(std::string_view st, const char *set)
{
    return set ? trimmed_if_front(st, is_one_of_chars(set)) : st;
}
//----------------------------------------------------------------------------

#else // no string_view

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
#endif

} // namespace
