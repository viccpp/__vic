// Iterator range sreaders
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_SREADERS_ITERATOR_H
#define __VIC_SREADERS_ITERATOR_H

#include<__vic/defs.h>
#include<__vic/sreaders/result.h>
#include<iterator>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<class Iter, class T = typename std::iterator_traits<Iter>::value_type>
class iterator_sreader
{
    Iter p, end;
public:
    iterator_sreader(Iter begin, Iter end) : p(begin), end(end) {}
    sread_result<T> operator()()
    {
        if(p != end) return static_cast<T>(*p++); // move?
        return sread_eof;
    }
    Iter position() const { return p; }
};
//////////////////////////////////////////////////////////////////////////////
template<class Iter, class T = typename std::iterator_traits<Iter>::value_type>
class iterator_sreader_n
{
    Iter p;
    size_t n;
public:
    iterator_sreader_n(Iter begin, size_t n) : p(begin), n(n) {}
    sread_result<T> operator()()
    {
        if(n != 0)
        {
            T v = *p; // move?
            ++p;
            n--;
            return v;
        }
        return sread_eof;
    }
    Iter position() const { return p; }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class Iter>
inline iterator_sreader<Iter> make_iterator_sreader(Iter begin, Iter end)
{
    return iterator_sreader<Iter>(begin, end);
}
//----------------------------------------------------------------------------
template<class T, class Iter>
inline iterator_sreader<Iter,T> make_iterator_sreader_for(Iter begin, Iter end)
{
    return iterator_sreader<Iter,T>(begin, end);
}
//----------------------------------------------------------------------------
template<class Iter>
inline iterator_sreader_n<Iter> make_iterator_sreader_n(Iter begin, size_t n)
{
    return iterator_sreader_n<Iter>(begin, n);
}
//----------------------------------------------------------------------------
template<class T, class Iter>
inline iterator_sreader_n<Iter,T> make_iterator_sreader_n_for(Iter begin, size_t n)
{
    return iterator_sreader_n<Iter,T>(begin, n);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
