// Template metaprogramming support
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_TYPE_TRAITS_H
#define __VIC_TYPE_TRAITS_H

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
using std::remove_reference;
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
    typedef typename remove_const<
        typename remove_volatile<T>::type>::type type;
};

//----------------------------------------------------------------------------

template<class T> struct remove_reference      { typedef T type; };
template<class T> struct remove_reference<T &> { typedef T type; };
#if __cpp_rvalue_references
template<class T> struct remove_reference<T &&> { typedef T type; };
#endif

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
template<> struct is_signed_integer<long> : true_type {};
template<> struct is_signed_integer<int> : true_type {};
template<> struct is_signed_integer<short> : true_type {};
template<> struct is_signed_integer<signed char> : true_type {};

template<class T> struct is_unsigned_integer : false_type {};
template<> struct is_unsigned_integer<unsigned long> : true_type {};
template<> struct is_unsigned_integer<unsigned int> : true_type {};
template<> struct is_unsigned_integer<unsigned short> : true_type {};
template<> struct is_unsigned_integer<unsigned char> : true_type {};

#ifdef __VIC_LONGLONG
template<> struct is_signed_integer<__VIC_LONGLONG> : true_type {};
template<> struct is_unsigned_integer<unsigned __VIC_LONGLONG> : true_type {};
#endif

//----------------------------------------------------------------------------

template<bool Test, class T = void>
struct disable_if : enable_if<!Test, T> {};

//----------------------------------------------------------------------------

template<class T> struct remove_cvref
{
    typedef typename remove_cv<
        typename remove_reference<T>::type>::type type;
};

//----------------------------------------------------------------------------

#if __cpp_alias_templates
template<class T> using remove_const_t = typename remove_const<T>::type;
template<class T> using remove_volatile_t = typename remove_volatile<T>::type;
template<class T> using remove_cv_t = typename remove_cv<T>::type;
template<class T> using remove_reference_t = typename remove_reference<T>::type;
template<class T> using remove_cvref_t = typename remove_cvref<T>::type;
template<class T> using remove_pointer_t = typename remove_pointer<T>::type;
// No alias for enable_if because in C++11 SFINAE is not guaranteed
#endif

//----------------------------------------------------------------------------

#if __cplusplus >= 201402L // C++14
using std::index_sequence;
using std::make_index_sequence;
#elif __cpp_variadic_templates && __cpp_alias_templates
//////////////////////////////////////////////////////////////////////////////
template<size_t... I>
struct index_sequence
{
    static constexpr size_t size() { return sizeof...(I); }
};
//////////////////////////////////////////////////////////////////////////////
// O(log N) implementation from here:
// http://stackoverflow.com/questions/17424477/implementation-c14-make-integer-sequence
template<typename Seq1, typename Seq2>
struct concat_sequence_;

template<size_t... I1, size_t... I2>
struct concat_sequence_<index_sequence<I1...>, index_sequence<I2...>>
{
    using type = index_sequence<I1..., (sizeof...(I1) + I2)...>;
};
//////////////////////////////////////////////////////////////////////////////
template<size_t Size>
struct make_index_sequence_ : concat_sequence_<
    typename make_index_sequence_<Size/2>::type,
    typename make_index_sequence_<Size - Size/2>::type
>{};
template<> struct make_index_sequence_<0> { using type = index_sequence<>; };
template<> struct make_index_sequence_<1> { using type = index_sequence<0>; };
//////////////////////////////////////////////////////////////////////////////
template<size_t Size>
using make_index_sequence = typename make_index_sequence_<Size>::type;
#endif

//----------------------------------------------------------------------------

} // namespace

#endif // header guard
