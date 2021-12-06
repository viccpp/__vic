// String utilities
//
// Platform: ISO C++ 98/11/17
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_STRING_UTILS_H
#define __VIC_STRING_UTILS_H

#include<__vic/defs.h>
#include<cstring>
#include<string>
#if __has_include(<string_view>)
#include<string_view>
#endif

namespace __vic {

//----------------------------------------------------------------------------
char *trim(char * ) noexcept;
char *trim_front(char * ) noexcept;
char *trim_back(char * ) noexcept;
char *trim(char * , char ) noexcept;
char *trim_front(char * , char ) noexcept;
char *trim_back(char * , char ) noexcept;
char *trim(char * , const char * ) noexcept;
char *trim_front(char * , const char * ) noexcept;
char *trim_back(char * , const char * ) noexcept;
//----------------------------------------------------------------------------
std::string &trim(std::string & );
std::string &trim_front(std::string & );
std::string &trim_back(std::string & );
std::string &trim(std::string & , char );
std::string &trim_front(std::string & , char );
std::string &trim_back(std::string & , char );
std::string &trim(std::string & , const char * );
std::string &trim_front(std::string & , const char * );
std::string &trim_back(std::string & , const char * );
//----------------------------------------------------------------------------
std::string trimmed(const std::string & );
std::string trimmed_front(const std::string & );
std::string trimmed_back(const std::string & );
std::string trimmed(const std::string & , char );
std::string trimmed_front(const std::string & , char );
std::string trimmed_back(const std::string & , char );
std::string trimmed(const std::string & , const char * );
std::string trimmed_front(const std::string & , const char * );
std::string trimmed_back(const std::string & , const char * );
//----------------------------------------------------------------------------

namespace impl {
//----------------------------------------------------------------------------
template<class Pred>
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
template<class Pred>
std::string &sift_if(std::string &st, Pred pred)
{
    std::string::iterator in = st.begin();
    while(in != st.end() && !pred(*in)) ++in;
    if(in == st.end()) return st; // no trash chars
    std::string::iterator out = in;
    while(++in != st.end())
        if(!pred(*in)) *out++ = *in;
    st.erase(out, st.end());
    return st;
}
//----------------------------------------------------------------------------
} // namespace

//----------------------------------------------------------------------------
char *sift(char * , const char * );
std::string &sift(std::string & , const char * );

template<class Pred>
char *sift_if(char *s, Pred pred) { return impl::sift_if(s, pred); }

template<class Pred>
std::string &sift_if(std::string &s, Pred pred) { return impl::sift_if(s, pred);}
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

} // namespace

#endif // header guard
