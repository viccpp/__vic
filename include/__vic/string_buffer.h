// Extended std::string, which has left-associative append
// operator (<<) and automatic conversion to c_str()
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_STRING_BUFFER_H
#define __VIC_STRING_BUFFER_H

#include<__vic/defs.h>
#include<__vic/to_text.h>
#include<__vic/string_ref.h>
#include<string>
#include<cstring>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Extended std::string, which has left-associative append
// operator (<<) and automatic conversion to c_str()
class string_buffer : public std::string
{
    typedef std::string base;
public:
    string_buffer() __VIC_DEFAULT_CTR
    explicit string_buffer(size_type n) { base::reserve(n); }
    string_buffer(const char *st) : base(st ? st : "") {}
    string_buffer(const std::string &st, size_type off = 0,
                        size_type n = npos) : base(st, off, n) {}
    string_buffer(string_ref sr) : base(sr.begin(), sr.size()) {}
    string_buffer(const char *st, size_type n) : base(st, n) {}
    string_buffer(const char *b, const char *e) : base(b, e - b) {}
    template<class InputIterator>
    string_buffer(InputIterator b, InputIterator e) : base(b, e) {}

    string_buffer &operator<<(const char *st) { return append(st); }
    string_buffer &operator<<(const std::string &st) { return append(st); }
    string_buffer &operator<<(string_ref sr) { return append(sr); }
    string_buffer &operator<<(char ch) { return *this += ch; }

    string_buffer &operator<<(long n) { to_text_append(n, *this); return *this; }
    string_buffer &operator<<(int n) { to_text_append(n, *this); return *this; }
    string_buffer &operator<<(short n) { to_text_append(n, *this); return *this; }
    string_buffer &operator<<(signed char n) { to_text_append(n, *this); return *this; }

    string_buffer &operator<<(unsigned long n) { to_text_append(n, *this); return *this; }
    string_buffer &operator<<(unsigned n) { to_text_append(n, *this); return *this; }
    string_buffer &operator<<(unsigned short n) { to_text_append(n, *this); return *this; }
    string_buffer &operator<<(unsigned char n) { to_text_append(n, *this); return *this; }

    string_buffer &operator<<(__VIC_LONGLONG n) { to_text_append(n, *this); return *this; }
    string_buffer &operator<<(unsigned __VIC_LONGLONG n) { to_text_append(n, *this); return *this; }

    string_buffer &operator<<(long double n) { to_text_append(n, *this); return *this; }
    string_buffer &operator<<(double n) { to_text_append(n, *this); return *this; }
    string_buffer &operator<<(float n) { to_text_append(n, *this); return *this; }

    string_buffer &operator<<(bool f) { to_text_append(f, *this); return *this; }
    string_buffer &operator<<(const void *p) { to_text_append(p, *this); return *this; }

    operator const char *() const { return c_str(); }

#if __cplusplus < 201103L
    // a missing container interface of std::string in C++98
    reference front() { return *begin(); }
    reference back() { return *rbegin(); }
    const_reference front() const { return *begin(); }
    const_reference back() const { return *rbegin(); }
    void pop_back() { erase(length() - 1); }
#endif

    // mapping for std::string operations
    string_buffer &operator=(char ch) { base::operator=(ch); return *this; }
    string_buffer &operator=(const char *st) { return assign(st); }
    string_buffer &operator=(const std::string &st) { return assign(st); }
    string_buffer &operator=(string_ref sr) { return assign(sr); }

    string_buffer &operator+=(char ch) { base::operator+=(ch); return *this; }
    string_buffer &operator+=(const char *st) { return append(st); }
    string_buffer &operator+=(const std::string &st) { return append(st); }
    string_buffer &operator+=(string_ref sr) { return append(sr); }

    string_buffer &assign(const char *st) { base::assign(st ? st : ""); return *this; }
    string_buffer &assign(const char *st, size_type n) { if(st) base::assign(st,n) ; return *this; }
    string_buffer &assign(const std::string &st) { base::assign(st); return *this; }
    string_buffer &assign(const std::string &st, size_type off, size_type n = npos) { base::assign(st,off,n); return *this; }
    string_buffer &assign(size_type n, char ch) { base::assign(n,ch); return *this; }
    template<class InputIterator>
    string_buffer &assign(InputIterator ib, InputIterator ie) { base::assign(ib,ie); return *this; }
    string_buffer &assign(string_ref sr) { base::assign(sr.begin(),sr.size()); return *this; }

    string_buffer &append(const char *st) { if(st) base::append(st); return *this; }
    string_buffer &append(const char *st, size_type n) { if(st) base::append(st,n); return *this; }
    string_buffer &append(const std::string &st) { base::append(st); return *this; }
    string_buffer &append(const std::string &st, size_type off, size_type n = npos) { base::append(st,off,n); return *this; }
    string_buffer &append(size_type n, char ch) { base::append(n,ch); return *this; }
    template<class InputIterator>
    string_buffer &append(InputIterator b, InputIterator e) { base::append(b,e); return *this; }
    string_buffer &append(string_ref sr) { base::append(sr.begin(),sr.size()); return *this; }

    using base::insert;
    string_buffer &insert(size_type pos, const char *st) { if(st) base::insert(pos,st); return *this; }
    string_buffer &insert(size_type pos, const char *st, size_type n) { if(st) base::insert(pos,st,n); return *this; }
    string_buffer &insert(size_type pos, const std::string &st) { base::insert(pos,st); return *this; }
    string_buffer &insert(size_type pos, const std::string &st, size_type off, size_type n = npos) { base::insert(pos,st,off,n); return *this; }
    string_buffer &insert(size_type pos, size_type n, char ch) { base::insert(pos,n,ch); return *this; }

    using base::erase;
    string_buffer &erase(size_type pos=0, size_type n=npos) { base::erase(pos,n); return *this; }

    string_buffer &replace(size_type pos, size_type n, const char *st) { if(st) base::replace(pos,n,st); return *this; }
    string_buffer &replace(size_type pos, size_type n1, const char *st, size_type n2) { if(st) base::replace(pos,n1,st,n2); return *this; }
    string_buffer &replace(size_type pos, size_type n, const std::string &st) { base::replace(pos,n,st); return *this; }
    string_buffer &replace(size_type pos1, size_type n1, const std::string &st, size_type pos2, size_type n2) { base::replace(pos1,n1,st,pos2,n2); return *this; }
    string_buffer &replace(size_type pos, size_type n, size_type count, char ch) { base::replace(pos,n,count,ch); return *this; }
    string_buffer &replace(__VIC_CXX11_CONST_ITERATOR b, __VIC_CXX11_CONST_ITERATOR e, const char *st) { if(st) base::replace(b,e,st); return *this; }
    string_buffer &replace(__VIC_CXX11_CONST_ITERATOR b, __VIC_CXX11_CONST_ITERATOR e, const std::string &st) { base::replace(b,e,st); return *this; }
    string_buffer &replace(__VIC_CXX11_CONST_ITERATOR b, __VIC_CXX11_CONST_ITERATOR e, const char *st, size_type n) { if(st) base::replace(b,e,st,n); return *this; }
    string_buffer &replace(__VIC_CXX11_CONST_ITERATOR b, __VIC_CXX11_CONST_ITERATOR e, size_type n, char ch) { base::replace(b,e,n,ch); return *this; }
    template<class InputIterator>
    string_buffer &replace(__VIC_CXX11_CONST_ITERATOR f, __VIC_CXX11_CONST_ITERATOR l, InputIterator b, InputIterator e) { base::replace(f,l,b,e); return *this; }

    string_buffer &reserve(size_type n) { base::reserve(n); return *this; }
    string_buffer &clear() { base::clear(); return *this; }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline string_buffer operator+(const string_buffer &s1, const std::string &s2)
{
    return string_buffer(s1.length() + s2.length()) << s1 << s2;
}
inline string_buffer operator+(const std::string &s1, const string_buffer &s2)
{
    return string_buffer(s1.length() + s2.length()) << s1 << s2;
}
inline string_buffer operator+(const string_buffer &s1, const string_buffer &s2)
{
    return s1 + static_cast<const std::string &>(s2);
}
inline string_buffer operator+(const string_buffer &s1, const char *s2)
{
    size_t n = s2 ? std::strlen(s2) : 0;
    return string_buffer(s1.length() + n).append(s1).append(s2, n);
}
inline string_buffer operator+(const char *s1, const string_buffer &s2)
{
    size_t n = s1 ? std::strlen(s1) : 0;
    return string_buffer(n + s2.length()).append(s1, n).append(s2);
}
inline string_buffer operator+(const string_buffer &s, char ch)
{
    return string_buffer(s.length() + 1) << s << ch;
}
inline string_buffer operator+(char ch, const string_buffer &s)
{
    return string_buffer(s.length() + 1) << ch << s;
}
#if __cpp_rvalue_references
inline string_buffer operator+(string_buffer &&s1, const std::string &s2)
{
    return std::move(s1 << s2);
}
inline string_buffer operator+(const std::string &s1, string_buffer &&s2)
{
    return std::move(s2.insert(0, s1));
}
inline string_buffer operator+(string_buffer &&s1, const string_buffer &s2)
{
    return std::move(s1) + static_cast<const std::string &>(s2);
}
inline string_buffer operator+(const string_buffer &s1, string_buffer &&s2)
{
    return static_cast<const std::string &>(s1) + std::move(s2);
}
inline string_buffer operator+(string_buffer &&s1, string_buffer &&s2)
{
    return std::move(s1 << s2);
}
inline string_buffer operator+(string_buffer &&s1, const char *s2)
{
    return std::move(s1 << s2);
}
inline string_buffer operator+(const char *s1, string_buffer &&s2)
{
    return std::move(s2.insert(0, s1));
}
inline string_buffer operator+(string_buffer &&s, char ch)
{
    return std::move(s << ch);
}
inline string_buffer operator+(char ch, string_buffer &&s)
{
    return std::move(s.insert(0, 1, ch));
}
#endif
//----------------------------------------------------------------------------

// Used primarly for creating messages with single expression
typedef string_buffer msg;

} // namespace

#endif // header guard
