// Container reader
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_READERS_CONTAINER_H
#define __VIC_READERS_CONTAINER_H

#include<__vic/readers/iterator.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
template<class Cont, class T = typename Cont::value_type>
struct container_reader :
    public iterator_reader<typename Cont::const_iterator, T>
{
    explicit container_reader(const Cont &c)
        : iterator_reader<typename Cont::const_iterator, T>(
            c.begin(), c.end()) {}
};
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
