// Generic utilities for elementwise reading
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_READERS_H
#define __VIC_READERS_H

#include<__vic/defs.h>
#include<iterator>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Expected reader's interface (concept)
//////////////////////////////////////////////////////////////////////////////
// template<class ElementT>
// interface Reader
// {
//     Reader(Reader && ); or Reader(const Reader & );
//     bool read(ElementT & ); // throws on errors
// };
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
template<class Iter, class T = typename std::iterator_traits<Iter>::value_type>
class range_reader
{
    Iter p, end;
public:
    range_reader(Iter begin, Iter end) : p(begin), end(end) {}
    bool read(T &v)
    {
        if(p == end) return false;
        v = *p++; // move?
        return true;
    }
};
//////////////////////////////////////////////////////////////////////////////
template<class Iter, class T = typename std::iterator_traits<Iter>::value_type>
class range_reader_n
{
    Iter p;
    size_t n;
public:
    range_reader_n(Iter begin, size_t n) : p(begin), n(n) {}
    bool read(T &v)
    {
        if(n == 0) return false;
        v = *p++; // move?
        n--;
        return true;
    }
};
//////////////////////////////////////////////////////////////////////////////
template<class Cont, class T = typename Cont::value_type>
struct container_reader : public range_reader<typename Cont::const_iterator, T>
{
    explicit container_reader(const Cont &c)
        : range_reader<typename Cont::const_iterator, T>(c.begin(), c.end()) {}
};
//////////////////////////////////////////////////////////////////////////////
template<class charT>
class basic_cstring_reader
{
    const charT *st;
public:
    explicit basic_cstring_reader(const charT *st) : st(st) {}
    bool read(charT &v)
    {
        if(!*st) return false;
        v = *st++;
        return true;
    }
};
//////////////////////////////////////////////////////////////////////////////
typedef basic_cstring_reader<char> cstring_reader;

} // namespace

#endif // header guard
