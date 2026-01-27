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
inline void trim_if_back(std::basic_string<charT,Traits,Alloc> &st, Pred pred)
{
    charT *begin = st.data(),
          *end = begin + st.length();
    charT *p = skip_if_back(begin, end, pred);
    if(p != end) st.resize(p - begin);
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc, class Pred>
inline void trim_if_front(std::basic_string<charT,Traits,Alloc> &st, Pred pred)
{
    charT *begin = st.data();
    charT *p = skip_if_front(begin, begin + st.length(), pred);
    if(p != begin) st.erase(0, p - begin);
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc, class Pred>
inline void trim_if(std::basic_string<charT,Traits,Alloc> &st, Pred pred)
{
    trim_if_back(st, pred);
    trim_if_front(st, pred);
}
//----------------------------------------------------------------------------

} // namespace

//----------------------------------------------------------------------------
std::string &trim(std::string &st)
{
    trim_if(st, is_ascii_ws());
    return st;
}
//----------------------------------------------------------------------------
std::string &trim_back(std::string &st)
{
    trim_if_back(st, is_ascii_ws());
    return st;
}
//----------------------------------------------------------------------------
std::string &trim_front(std::string &st)
{
    trim_if_front(st, is_ascii_ws());
    return st;
}
//----------------------------------------------------------------------------
std::string &trim(std::string &st, char ch)
{
    trim_if(st, is_eq_char(ch));
    return st;
}
//----------------------------------------------------------------------------
std::string &trim_back(std::string &st, char ch)
{
    trim_if_back(st, is_eq_char(ch));
    return st;
}
//----------------------------------------------------------------------------
std::string &trim_front(std::string &st, char ch)
{
    trim_if_front(st, is_eq_char(ch));
    return st;
}
//----------------------------------------------------------------------------
std::string &trim(std::string &st, const char *set)
{
    if(set) trim_if(st, is_one_of_chars(set));
    return st;
}
//----------------------------------------------------------------------------
std::string &trim_back(std::string &st, const char *set)
{
    if(set) trim_if_back(st, is_one_of_chars(set));
    return st;
}
//----------------------------------------------------------------------------
std::string &trim_front(std::string &st, const char *set)
{
    if(set) trim_if_front(st, is_one_of_chars(set));
    return st;
}
//----------------------------------------------------------------------------

} // namespace
