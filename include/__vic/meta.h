// Template metaprogramming support
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_META_H
#define __VIC_META_H

#include<__vic/defs.h>
#if __cplusplus >= 201103L && !defined(__VIC_HAVE_TYPE_TRAITS)
#define __VIC_HAVE_TYPE_TRAITS 1
#endif
#ifdef __VIC_HAVE_TYPE_TRAITS
#include<type_traits>
#endif

namespace __vic {

#ifdef __VIC_HAVE_TYPE_TRAITS

//----------------------------------------------------------------------------

using std::integral_constant;
using std::true_type;
using std::false_type;
using std::is_same;
using std::is_const;
using std::remove_const;
using std::remove_volatile;
using std::remove_cv;
using std::remove_pointer;
using std::enable_if;

//----------------------------------------------------------------------------

#else // no <type_traits>

//////////////////////////////////////////////////////////////////////////////
// Convenient template for integral constant types
template<class T, T Val>
struct integral_constant
{
    typedef T value_type;
    typedef integral_constant<T, Val> type;

    static const T value = Val;
};
//////////////////////////////////////////////////////////////////////////////
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

//----------------------------------------------------------------------------

template<class T1, class T2> struct is_same : false_type {};
template<class T> struct is_same<T,T> : true_type {};

//----------------------------------------------------------------------------

template<class T> struct is_const : false_type {};
template<class T> struct is_const<const T> : true_type {};

//----------------------------------------------------------------------------

template<class T> struct remove_const          { typedef T type; };
template<class T> struct remove_const<const T> { typedef T type; };

//----------------------------------------------------------------------------

template<class T> struct remove_volatile             { typedef T type; };
template<class T> struct remove_volatile<volatile T> { typedef T type; };

//----------------------------------------------------------------------------

template<class T> struct remove_cv
{
    typedef typename
    remove_const<typename remove_volatile<T>::type>::type type;
};

//----------------------------------------------------------------------------

template<class T> struct remove_pointer      { typedef T type; };
template<class T> struct remove_pointer<T *> { typedef T type; };

//----------------------------------------------------------------------------

template<bool Test, class T = void>
struct enable_if
{
    typedef T type;
};
template<class T>
struct enable_if<false, T> {};

//----------------------------------------------------------------------------

#endif // __VIC_HAVE_TYPE_TRAITS

//----------------------------------------------------------------------------

template<class T> struct is_signed_integer : false_type {};
template<> struct is_signed_integer<__VIC_LONGLONG> : true_type {};
template<> struct is_signed_integer<long> : true_type {};
template<> struct is_signed_integer<int> : true_type {};
template<> struct is_signed_integer<short> : true_type {};
template<> struct is_signed_integer<signed char> : true_type {};

template<class T> struct is_unsigned_integer : false_type {};
template<> struct is_unsigned_integer<unsigned __VIC_LONGLONG> : true_type {};
template<> struct is_unsigned_integer<unsigned long> : true_type {};
template<> struct is_unsigned_integer<unsigned int> : true_type {};
template<> struct is_unsigned_integer<unsigned short> : true_type {};
template<> struct is_unsigned_integer<unsigned char> : true_type {};

//----------------------------------------------------------------------------

template<bool Test, class T = void>
struct disable_if : enable_if<!Test, T> {};

//----------------------------------------------------------------------------

} // namespace

#endif // header guard
