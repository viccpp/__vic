// WCHAR-related utils
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_WINDOWS_WCHAR_H
#define __VIC_WINDOWS_WCHAR_H

#include<__vic/defs.h>
#include<string>
#if __has_include(<string_view>)
#include<string_view>
#endif

namespace __vic { namespace windows {

//////////////////////////////////////////////////////////////////////////////
class wstring : public std::wstring
{
    typedef std::wstring base;
public:
    wstring() __VIC_DEFAULT_CTR
    explicit wstring(size_type n) { reserve(n); }
    wstring(const wchar_t *st) : base(st) {}
#if __cpp_rvalue_references
    wstring(std::wstring st) : base(std::move(st)) {}
#else
    wstring(const std::wstring &st) : base(st) {}
#endif

    operator const wchar_t *() const { return c_str(); }
};
//////////////////////////////////////////////////////////////////////////////

wstring utf8to16(const char * , size_t );
std::string utf16to8(const wchar_t * , size_t );
std::string &utf16to8_append(const wchar_t * , size_t , std::string & );

#if __cpp_lib_string_view // C++17
inline wstring utf8to16(std::string_view s)
    { return utf8to16(s.data(), s.length()); }
inline std::string utf16to8(std::wstring_view s)
    { return utf16to8(s.data(), s.length()); }
inline std::string &utf16to8_append(std::wstring_view s, std::string &res)
    { return utf16to8_append(s.data(), s.length(), res); }
#else
inline wstring utf8to16(const char *s)
    { return utf8to16(s, std::char_traits<char>::length(s)); }
inline wstring utf8to16(const std::string &s)
    { return utf8to16(s.data(), s.length()); }

inline std::string utf16to8(const wchar_t *s)
    { return utf16to8(s, std::char_traits<wchar_t>::length(s)); }
inline std::string utf16to8(const std::wstring &s)
    { return utf16to8(s.data(), s.length()); }

inline std::string &utf16to8_append(const wchar_t *s, std::string &res)
{
    return utf16to8_append(s, std::char_traits<wchar_t>::length(s), res);
}
inline std::string &utf16to8_append(const std::wstring &s, std::string &res)
{
    return utf16to8_append(s.data(), s.length(), res);
}
#endif

}} // namespace

#endif // header guard
