// Output iterator writer
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2018

#ifndef __VIC_WRITERS_ITERATOR_H
#define __VIC_WRITERS_ITERATOR_H

#include<__vic/defs.h>
#include<iterator>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<class Iter, class T = typename std::iterator_traits<Iter>::value_type>
class iterator_writer
{
    Iter p;
public:
    explicit iterator_writer(Iter it) : p(it) {}
    void write(T v) { *p++ = v; }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class Iter>
inline iterator_writer<Iter> make_iterator_writer(Iter it)
{
    return iterator_writer<Iter>(it);
}
//----------------------------------------------------------------------------
template<class T, class Iter>
inline iterator_writer<Iter,T> make_iterator_writer_for(Iter it)
{
    return iterator_writer<Iter,T>(it);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
