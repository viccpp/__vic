// NULL-terminated C-string reader
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_READERS_CSTRING_H
#define __VIC_READERS_CSTRING_H

#include<__vic/defs.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Internal implementation class
template<class charT>
class basic_cstring_reader_
{
    const charT *st;
public:
    explicit basic_cstring_reader_(const charT *s) : st(s) {}
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
class basic_cstring_reader
{
    basic_cstring_reader_<charT> r;
public:
    explicit basic_cstring_reader(const charT *s) : r(s) {}
    bool read(charT &ch) { return r.read(ch); }
    const charT *position() const { return r.position(); }
};
//////////////////////////////////////////////////////////////////////////////
// Reader<char> + Reader<unsigned char>
template<>
class basic_cstring_reader<char>
{
    basic_cstring_reader_<char> r;
public:
    explicit basic_cstring_reader(const char *s) : r(s) {}
    bool read(char &ch) { return r.read(ch); }
    bool read(unsigned char &ch) { return read(reinterpret_cast<char&>(ch)); }
    const char *position() const { return r.position(); }
};
//////////////////////////////////////////////////////////////////////////////
typedef basic_cstring_reader<char> cstring_reader;

} // namespace

#endif // header guard
