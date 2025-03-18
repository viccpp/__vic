// Value parser for std::list
//
// Platform: ISO C++ 11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_CONFIG_VALUES_STD_LIST_H
#define __VIC_CONFIG_VALUES_STD_LIST_H

#include<__vic/config/value.h>
#include<list>

namespace __vic { namespace config {

//////////////////////////////////////////////////////////////////////////////
template<class T>
struct list_traits<std::list<T> >
{
    typedef T value_type;
    static void push(std::list<T> &c, T &&v) { c.push_back(std::move(v)); }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
