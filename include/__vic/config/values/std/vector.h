// Value parser for std::vector
//
// Platform: ISO C++ 11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_CONFIG_VALUES_STD_VECTOR_H
#define __VIC_CONFIG_VALUES_STD_VECTOR_H

#include<__vic/config/value.h>
#include<vector>

namespace __vic { namespace config {

//////////////////////////////////////////////////////////////////////////////
template<class T>
struct list_traits<std::vector<T> >
{
    typedef T value_type;
    static void push(std::vector<T> &c, T &&v) { c.push_back(std::move(v)); }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
