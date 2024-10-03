// Container sreader
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_SREADERS_CONTAINER_H
#define __VIC_SREADERS_CONTAINER_H

#include<__vic/sreaders/iterator.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<class Cont, class T = typename Cont::value_type>
struct container_sreader :
    public iterator_sreader<typename Cont::const_iterator, T>
{
    explicit container_sreader(const Cont &c)
        : iterator_sreader<typename Cont::const_iterator, T>(
            c.begin(), c.end()) {}
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class Cont>
inline container_sreader<Cont> make_container_sreader(const Cont &c)
{
    return container_sreader<Cont>(c);
}
//----------------------------------------------------------------------------
template<class T, class Cont>
inline container_sreader<Cont,T> make_container_sreader_for(const Cont &c)
{
    return container_sreader<Cont,T>(c);
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
