// Output iterator swriter
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2018

#ifndef __VIC_SWRITERS_ITERATOR_H
#define __VIC_SWRITERS_ITERATOR_H

#include<__vic/defs.h>
#include<iterator>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<class Iter, class T = typename std::iterator_traits<Iter>::value_type>
class iterator_swriter
{
    Iter p;
public:
    explicit iterator_swriter(Iter it) : p(it) {}
    void write(T v) { *p++ = v; }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class Iter>
inline iterator_swriter<Iter> make_iterator_swriter(Iter it)
{
    return iterator_swriter<Iter>(it);
}
//----------------------------------------------------------------------------
template<class T, class Iter>
inline iterator_swriter<Iter,T> make_iterator_swriter_for(Iter it)
{
    return iterator_swriter<Iter,T>(it);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
