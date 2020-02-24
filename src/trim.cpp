//
// $Id$
//

#include<__vic/string_utils.h>
#include<__vic/tchar.h>

namespace __vic {

namespace {

const char spaces[] = " \t\n\r\f\v";

//----------------------------------------------------------------------------
template<class charT>
inline charT *trim_b(charT *st, charT space)
{
    charT *p = tchar::end(st) - 1;
    while(p >= st && *p == space) p--;
    *(++p) = charT();
    return st;
}
//----------------------------------------------------------------------------
template<class charT>
inline charT *trim_f(charT *st, charT space)
{
    charT *p = st;
    while(*p == space) p++;
    if(p != st) tchar::move(st, p);
    return st;
}
//----------------------------------------------------------------------------
template<class charT>
inline charT *trim_b(charT *st, const charT *set)
{
    charT *p = tchar::find_last_not_of(st, set);
    if(p) *(p+1) = charT(); else *st = charT();
    return st;
}
//----------------------------------------------------------------------------
template<class charT>
inline charT *trim_f(charT *st, const charT *set)
{
    charT *p = tchar::find_first_not_of(st, set);
    if(p)
    {
        if(p != st) tchar::move(st, p);
    }
    else *st = charT();
    return st;
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc>
inline std::basic_string<charT,Traits,Alloc> &trim_b(
    std::basic_string<charT,Traits,Alloc> &st, charT space)
{
    typedef std::basic_string<charT,Traits,Alloc> str_t;
    typename str_t::size_type pos = st.find_last_not_of(space);
    st.resize(pos != str_t::npos ? pos+1 : 0);
    return st;
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc>
inline std::basic_string<charT,Traits,Alloc> &trim_f(
    std::basic_string<charT,Traits,Alloc> &st, charT space)
{
    typedef std::basic_string<charT,Traits,Alloc> str_t;
    typename str_t::size_type pos = st.find_first_not_of(space);
    if(pos != 0) st.erase(0, pos);
    return st;
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc>
inline std::basic_string<charT,Traits,Alloc> &trim_b(
    std::basic_string<charT,Traits,Alloc> &st, const charT *set)
{
    typedef std::basic_string<charT,Traits,Alloc> str_t;
    typename str_t::size_type pos = st.find_last_not_of(set);
    st.resize(pos != str_t::npos ? pos+1 : 0);
    return st;
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc>
inline std::basic_string<charT,Traits,Alloc> &trim_f(
    std::basic_string<charT,Traits,Alloc> &st, const charT *set)
{
    typedef std::basic_string<charT,Traits,Alloc> str_t;
    typename str_t::size_type pos = st.find_first_not_of(set);
    if(pos != 0) st.erase(0, pos);
    return st;
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc>
inline typename std::basic_string<charT,Traits,Alloc>::const_iterator
    trimmed_begin(const std::basic_string<charT,Traits,Alloc> &st, charT space)
{
    typedef std::basic_string<charT,Traits,Alloc> str_t;
    typename str_t::size_type pos = st.find_first_not_of(space);
    return pos != str_t::npos ? st.begin() + pos : st.begin();
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc>
inline typename std::basic_string<charT,Traits,Alloc>::const_iterator
    trimmed_end(const std::basic_string<charT,Traits,Alloc> &st, charT space)
{
    typedef std::basic_string<charT,Traits,Alloc> str_t;
    typename str_t::size_type pos = st.find_last_not_of(space);
    return pos != str_t::npos ? st.begin() + pos + 1 : st.begin();
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc>
inline typename std::basic_string<charT,Traits,Alloc>::const_iterator
    trimmed_begin(const std::basic_string<charT,Traits,Alloc> &st, const charT *set)
{
    typedef std::basic_string<charT,Traits,Alloc> str_t;
    typename str_t::size_type pos = st.find_first_not_of(set);
    return pos != str_t::npos ? st.begin() + pos : st.begin();
}
//----------------------------------------------------------------------------
template<class charT, class Traits, class Alloc>
inline typename std::basic_string<charT,Traits,Alloc>::const_iterator
    trimmed_end(const std::basic_string<charT,Traits,Alloc> &st, const charT *set)
{
    typedef std::basic_string<charT,Traits,Alloc> str_t;
    typename str_t::size_type pos = st.find_last_not_of(set);
    return pos != str_t::npos ? st.begin() + pos + 1 : st.begin();
}
//----------------------------------------------------------------------------

} // namespace

//----------------------------------------------------------------------------
char *trim(char *st) noexcept
{
    return st ? trim_f(trim_b(st, spaces), spaces) : st;
}
//----------------------------------------------------------------------------
char *trim_back(char *st) noexcept
{
    return st ? trim_b(st, spaces) : st;
}
//----------------------------------------------------------------------------
char *trim_front(char *st) noexcept
{
    return st ? trim_f(st, spaces) : st;
}
//----------------------------------------------------------------------------
char *trim(char *st, char space) noexcept
{
    return st ? trim_f(trim_b(st, space), space) : st;
}
//----------------------------------------------------------------------------
char *trim_back(char *st, char space) noexcept
{
    return st ? trim_b(st, space) : st;
}
//----------------------------------------------------------------------------
char *trim_front(char *st, char space) noexcept
{
    return st ? trim_f(st, space) : st;
}
//----------------------------------------------------------------------------
char *trim(char *st, const char *set) noexcept
{
    return st && set ? trim_f(trim_b(st, set), set) : st;
}
//----------------------------------------------------------------------------
char *trim_back(char *st, const char *set) noexcept
{
    return st && set ? trim_b(st, set) : st;
}
//----------------------------------------------------------------------------
char *trim_front(char *st, const char *set) noexcept
{
    return st && set ? trim_f(st, set) : st;
}
//----------------------------------------------------------------------------
std::string &trim(std::string &st)
{
    return trim_f(trim_b(st, spaces), spaces);
}
//----------------------------------------------------------------------------
std::string &trim_back(std::string &st)
{
    return trim_b(st, spaces);
}
//----------------------------------------------------------------------------
std::string &trim_front(std::string &st)
{
    return trim_f(st, spaces);
}
//----------------------------------------------------------------------------
std::string &trim(std::string &st, char space)
{
    return trim_f(trim_b(st, space), space);
}
//----------------------------------------------------------------------------
std::string &trim_back(std::string &st, char space)
{
    return trim_b(st, space);
}
//----------------------------------------------------------------------------
std::string &trim_front(std::string &st, char space)
{
    return trim_f(st, space);
}
//----------------------------------------------------------------------------
std::string &trim(std::string &st, const char *set)
{
    return set ? trim_f(trim_b(st, set), set) : st;
}
//----------------------------------------------------------------------------
std::string &trim_back(std::string &st, const char *set)
{
    return set ? trim_b(st, set) : st;
}
//----------------------------------------------------------------------------
std::string &trim_front(std::string &st, const char *set)
{
    return set ? trim_f(st, set) : st;
}
//----------------------------------------------------------------------------
std::string trimmed(const std::string &st)
{
    return std::string(trimmed_begin(st, spaces), trimmed_end(st, spaces));
}
//----------------------------------------------------------------------------
std::string trimmed_back(const std::string &st)
{
    return std::string(st.begin(), trimmed_end(st, spaces));
}
//----------------------------------------------------------------------------
std::string trimmed_front(const std::string &st)
{
    return std::string(trimmed_begin(st, spaces), st.end());
}
//----------------------------------------------------------------------------
std::string trimmed(const std::string &st, char space)
{
    return std::string(trimmed_begin(st, space), trimmed_end(st, space));
}
//----------------------------------------------------------------------------
std::string trimmed_back(const std::string &st, char space)
{
    return std::string(st.begin(), trimmed_end(st, space));
}
//----------------------------------------------------------------------------
std::string trimmed_front(const std::string &st, char space)
{
    return std::string(trimmed_begin(st, space), st.end());
}
//----------------------------------------------------------------------------
std::string trimmed(const std::string &st, const char *set)
{
    return set ?
        std::string(trimmed_begin(st, set), trimmed_end(st, set)) : st;
}
//----------------------------------------------------------------------------
std::string trimmed_back(const std::string &st, const char *set)
{
    return set ? std::string(st.begin(), trimmed_end(st, set)) : st;
}
//----------------------------------------------------------------------------
std::string trimmed_front(const std::string &st, const char *set)
{
    return set ? std::string(trimmed_begin(st, set), st.end()) : st;
}
//----------------------------------------------------------------------------

} // namespace
