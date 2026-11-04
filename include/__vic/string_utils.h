// String utilities
//
// Platform: ISO C++ 98/11/17
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_STRING_UTILS_H
#define __VIC_STRING_UTILS_H

#include<__vic/defs.h>
#include<__vic/set_of_chars.h>
#include<cstring>
#include<string>
#if __has_include(<string_view>)
#include<string_view>
#endif
#if __has_include(<concepts>)
#include<concepts>
#endif
#if __cpp_lib_string_view
#include<__vic/ascii.h>
#endif

#if __cpp_lib_concepts
#define __VIC_STD_PREDICATE(t) std::predicate<t>
#else
#define __VIC_STD_PREDICATE(t) class
#endif

namespace __vic {

//----------------------------------------------------------------------------
char *trim(char * ) noexcept;
char *trim_front(char * ) noexcept;
char *trim_back(char * ) noexcept;
char *trim(char * , char ) noexcept;
char *trim_front(char * , char ) noexcept;
char *trim_back(char * , char ) noexcept;
char *trim(char * , const set_of_chars & ) noexcept;
char *trim_front(char * , const set_of_chars & ) noexcept;
char *trim_back(char * , const set_of_chars & ) noexcept;
//----------------------------------------------------------------------------
std::string &trim(std::string & );
std::string &trim_front(std::string & );
std::string &trim_back(std::string & );
std::string &trim(std::string & , char );
std::string &trim_front(std::string & , char );
std::string &trim_back(std::string & , char );
std::string &trim(std::string & , const set_of_chars & );
std::string &trim_front(std::string & , const set_of_chars & );
std::string &trim_back(std::string & , const set_of_chars & );
//----------------------------------------------------------------------------

#if __cpp_lib_string_view // C++17
//----------------------------------------------------------------------------
template<class charT, class Traits, __VIC_STD_PREDICATE(charT) Pred>
constexpr std::basic_string_view<charT, Traits> &trim_front_if(
    std::basic_string_view<charT, Traits> &s, Pred pred)
{
    auto p = s.data(), end = p + s.length();
    if(p != end && pred(*p))
    {
        while(++p != end && pred(*p));
        s = {p, static_cast<std::size_t>(end - p)};
    }
    return s;
}
//----------------------------------------------------------------------------
template<class charT, class Traits, __VIC_STD_PREDICATE(charT) Pred>
constexpr std::basic_string_view<charT, Traits> &trim_back_if(
    std::basic_string_view<charT, Traits> &s, Pred pred)
{
    auto begin = s.data(), p = begin + s.length();
    if(p != begin && pred(*(p - 1)))
    {
        while(--p != begin && pred(*(p - 1)));
        s = {begin, static_cast<std::size_t>(p - begin)};
        //s.remove_suffix(static_cast<std::size_t>(end - p));
    }
    return s;
}
//----------------------------------------------------------------------------
template<class charT, class Traits, __VIC_STD_PREDICATE(charT) Pred>
constexpr std::basic_string_view<charT, Traits> &trim_if(
    std::basic_string_view<charT, Traits> &s, Pred pred)
{
    return trim_front_if(trim_back_if(s, pred), pred);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
constexpr std::string_view &trim(std::string_view &s)
{
    return trim_if(s, [](char c){ return ascii::isspace(c); });
}
constexpr std::string_view &trim_front(std::string_view &s)
{
    return trim_front_if(s, [](char c){ return ascii::isspace(c); });
}
constexpr std::string_view &trim_back(std::string_view &s)
{
    return trim_back_if(s, [](char c){ return ascii::isspace(c); });
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
constexpr std::string_view &trim(std::string_view &s, char ch)
{
    return trim_if(s, [ch](char c){ return c == ch; });
}
constexpr std::string_view &trim_front(std::string_view &s, char ch)
{
    return trim_front_if(s, [ch](char c){ return c == ch; });
}
constexpr std::string_view &trim_back(std::string_view &s, char ch)
{
    return trim_back_if(s, [ch](char c){ return c == ch; });
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
constexpr std::string_view &trim(std::string_view &s, const set_of_chars &set)
{
    return trim_if(s, [&](char c){ return set.contains(c); });
}
constexpr
std::string_view &trim_front(std::string_view &s, const set_of_chars &set)
{
    return trim_front_if(s, [&](char c){ return set.contains(c); });
}
constexpr
std::string_view &trim_back(std::string_view &s, const set_of_chars &set)
{
    return trim_back_if(s, [&](char c){ return set.contains(c); });
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
constexpr std::string_view trimmed(std::string_view s)
{
    return trim(s);
}
constexpr std::string_view trimmed_front(std::string_view s)
{
    return trim_front(s);
}
constexpr std::string_view trimmed_back(std::string_view s)
{
    return trim_back(s);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
__VIC_NODISCARD constexpr std::string_view trimmed(std::string_view s, char ch)
{
    return trim(s, ch);
}
__VIC_NODISCARD
constexpr std::string_view trimmed_front(std::string_view s, char ch)
{
    return trim_front(s, ch);
}
__VIC_NODISCARD
constexpr std::string_view trimmed_back(std::string_view s, char ch)
{
    return trim_back(s, ch);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
__VIC_NODISCARD constexpr
std::string_view trimmed(std::string_view s, const set_of_chars &set)
{
    return trim(s, set);
}
__VIC_NODISCARD constexpr
std::string_view trimmed_front(std::string_view s, const set_of_chars &set)
{
    return trim_front(s, set);
}
__VIC_NODISCARD constexpr
std::string_view trimmed_back(std::string_view s, const set_of_chars &set)
{
    return trim_back(s, set);
}
//----------------------------------------------------------------------------
#else // until C++17
std::string trimmed(const std::string & );
std::string trimmed_front(const std::string & );
std::string trimmed_back(const std::string & );
std::string trimmed(const std::string & , char );
std::string trimmed_front(const std::string & , char );
std::string trimmed_back(const std::string & , char );
std::string trimmed(const std::string & , const set_of_chars & );
std::string trimmed_front(const std::string & , const set_of_chars & );
std::string trimmed_back(const std::string & , const set_of_chars & );
#endif
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template<__VIC_STD_PREDICATE(char) Pred>
inline char *sift_if(char *st, Pred pred)
{
    if(!st) return st;
    char *in = st;
    while(*in && !pred(*in)) in++;
    if(!*in) return st; // no trash chars
    char *out = in;
    while(char ch = *++in)
        if(!pred(ch)) *out++ = ch;
    *out = '\0';
    return st;
}
//----------------------------------------------------------------------------
template<__VIC_STD_PREDICATE(char) Pred>
inline std::string &sift_if(std::string &st, Pred pred)
{
    // data() is const in C++98
    char *in = &st[0], *end = in + st.length();
    while(in != end && !pred(*in)) ++in;
    if(in == end) return st; // no trash chars
    char *out = in;
    while(++in != end)
        if(!pred(*in)) *out++ = *in;
    st.resize(out - st.data());
    return st;
}
//----------------------------------------------------------------------------
char *sift(char * , const set_of_chars & );
std::string &sift(std::string & , const set_of_chars & );
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
std::string &pad_front(std::string & , size_t , char = ' ');
std::string &pad_back(std::string & , size_t , char = ' ');
char *pad_front(char * , size_t , char = ' ');
char *pad_back(char * , size_t , char = ' ');
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
inline bool starts_with(const char *s, size_t s_len, char pref)
{
    return s_len && *s == pref;
}
bool starts_with(const char * , size_t , const char * );
bool starts_with(const char * , size_t , const char * , size_t );
//----------------------------------------------------------------------------
inline bool starts_with(const char *s, char pref)
{
    return *s == pref;
}
bool starts_with(const char * , const char * );
bool starts_with(const char * , const char * , size_t );
//----------------------------------------------------------------------------
#if __cpp_lib_string_view // C++17
//----------------------------------------------------------------------------
inline bool starts_with(std::string_view s, char pref)
{
    return !s.empty() && s.front() == pref;
}
inline bool starts_with(std::string_view s, std::string_view pref)
{
    return starts_with(s.data(), s.length(), pref.data(), pref.length());
}
inline bool starts_with(std::string_view s, const char *pref)
{
    return starts_with(s.data(), s.length(), pref);
}
//----------------------------------------------------------------------------
#else // until C++17
//----------------------------------------------------------------------------
inline bool starts_with(const std::string &s, char pref)
{
    return !s.empty() && *s.begin() == pref;
}
inline bool starts_with(const std::string &s, const char *pref)
{
    return starts_with(s.data(), s.length(), pref);
}
inline bool starts_with(const std::string &s, const char *pref, size_t pref_len)
{
    return starts_with(s.data(), s.length(), pref, pref_len);
}
inline bool starts_with(const std::string &s, const std::string &pref)
{
    return starts_with(s, pref.data(), pref.length());
}
//----------------------------------------------------------------------------
#endif

//----------------------------------------------------------------------------
inline bool ends_with(const char *s, size_t s_len, char suff)
{
    return s_len && s[s_len - 1] == suff;
}
bool ends_with(const char * , size_t , const char * , size_t );
//----------------------------------------------------------------------------
#if __cpp_lib_string_view // C++17
//----------------------------------------------------------------------------
inline bool ends_with(std::string_view s, char suff)
{
    return ends_with(s.data(), s.length(), suff);
}
inline bool ends_with(std::string_view s, std::string_view suff)
{
    return ends_with(s.data(), s.length(), suff.data(), suff.length());
}
//----------------------------------------------------------------------------
#else // until C++17
//----------------------------------------------------------------------------
inline bool ends_with(const char *s, char suff)
{
    return ends_with(s, std::strlen(s), suff);
}
inline bool ends_with(const char *s, size_t s_len, const char *suff)
{
    return ends_with(s, s_len, suff, std::strlen(suff));
}
inline bool ends_with(const char *s, const char *suff, size_t suff_len)
{
    return ends_with(s, std::strlen(s), suff, suff_len);
}
inline bool ends_with(const char *s, const char *suff)
{
    return ends_with(s, suff, std::strlen(suff));
}
//----------------------------------------------------------------------------
inline bool ends_with(const std::string &s, char suff)
{
    return !s.empty() && *s.rbegin() == suff;
}
inline bool ends_with(const std::string &s, const char *suff)
{
    return ends_with(s.data(), s.length(), suff);
}
inline bool ends_with(const std::string &s, const char *suff, size_t suff_len)
{
    return ends_with(s.data(), s.length(), suff, suff_len);
}
inline bool ends_with(const std::string &s, const std::string &suff)
{
    return ends_with(s, suff.data(), suff.length());
}
//----------------------------------------------------------------------------
#endif

#undef __VIC_STD_PREDICATE

} // namespace

#endif // header guard
