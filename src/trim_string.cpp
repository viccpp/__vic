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
inline void trim_back_if(std::basic_string<charT,Traits,Alloc> &st, Pred pred)
{
    charT *begin = &*st.begin(), // data() is const in C++98
          *end = begin + st.length();
    charT *p = skip_back_if(begin, end, pred);
    if(p != end) st.resize(p - begin);
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc, class Pred>
inline void trim_front_if(std::basic_string<charT,Traits,Alloc> &st, Pred pred)
{
    charT *begin = &*st.begin();
    charT *p = skip_front_if(begin, begin + st.length(), pred);
    if(p != begin) st.erase(0, p - begin);
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc, class Pred>
inline void trim_if(std::basic_string<charT,Traits,Alloc> &st, Pred pred)
{
    trim_back_if(st, pred);
    trim_front_if(st, pred);
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
    trim_back_if(st, is_ascii_ws());
    return st;
}
//----------------------------------------------------------------------------
std::string &trim_front(std::string &st)
{
    trim_front_if(st, is_ascii_ws());
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
    trim_back_if(st, is_eq_char(ch));
    return st;
}
//----------------------------------------------------------------------------
std::string &trim_front(std::string &st, char ch)
{
    trim_front_if(st, is_eq_char(ch));
    return st;
}
//----------------------------------------------------------------------------
std::string &trim(std::string &st, const set_of_chars &set)
{
    trim_if(st, is_one_of_chars(set));
    return st;
}
//----------------------------------------------------------------------------
std::string &trim_back(std::string &st, const set_of_chars &set)
{
    trim_back_if(st, is_one_of_chars(set));
    return st;
}
//----------------------------------------------------------------------------
std::string &trim_front(std::string &st, const set_of_chars &set)
{
    trim_front_if(st, is_one_of_chars(set));
    return st;
}
//----------------------------------------------------------------------------

} // namespace
