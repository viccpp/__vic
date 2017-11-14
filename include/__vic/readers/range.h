// Range readers
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_READERS_RANGE_H
#define __VIC_READERS_RANGE_H

#include<__vic/defs.h>
#include<iterator>

namespace __vic {

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

} // namespace

#endif // header guard
