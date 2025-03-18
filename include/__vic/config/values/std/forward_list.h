// Value parser for std::forward_list
//
// Platform: ISO C++ 11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_CONFIG_VALUES_STD_FORWARD_LIST_H
#define __VIC_CONFIG_VALUES_STD_FORWARD_LIST_H

#include<__vic/config/value.h>
#include<forward_list>

namespace __vic { namespace config {

//////////////////////////////////////////////////////////////////////////////
template<class T>
struct list_traits<std::forward_list<T>>
{
    typedef T value_type;
    static void push(std::forward_list<T> &c, T &&v)
        { c.push_front(std::move(v)); }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
