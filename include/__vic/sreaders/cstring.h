// NULL-terminated C-string sreader
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_SREADERS_CSTRING_H
#define __VIC_SREADERS_CSTRING_H

#include<__vic/defs.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Internal implementation class
template<class charT>
class basic_cstring_sreader_
{
    const charT *st;
public:
    explicit basic_cstring_sreader_(const charT *s) : st(s) {}
    bool read(charT &ch)
    {
        if(!*st) return false;
        ch = *st++;
        return true;
    }
    const charT *position() const { return st; }
};
//////////////////////////////////////////////////////////////////////////////
template<class charT>
class basic_cstring_sreader
{
    basic_cstring_sreader_<charT> r;
public:
    explicit basic_cstring_sreader(const charT *s) : r(s) {}
    bool read(charT &ch) { return r.read(ch); }
    const charT *position() const { return r.position(); }
};
//////////////////////////////////////////////////////////////////////////////
// sreader<char> + sreader<unsigned char>
template<>
class basic_cstring_sreader<char>
{
    basic_cstring_sreader_<char> r;
public:
    explicit basic_cstring_sreader(const char *s) : r(s) {}
    bool operator()(char &ch) { return r.read(ch); }
    bool operator()(unsigned char &ch) { return (*this)(reinterpret_cast<char&>(ch)); }
    const char *position() const { return r.position(); }
};
//////////////////////////////////////////////////////////////////////////////
typedef basic_cstring_sreader<char> cstring_sreader;

//----------------------------------------------------------------------------
template<class charT>
inline basic_cstring_sreader<charT> make_cstring_sreader(const charT *s)
{
    return basic_cstring_sreader<charT>(s);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
