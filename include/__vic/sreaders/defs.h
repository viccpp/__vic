// Generic utility for sequential one by one elements reading (input)
//
// Platform: ISO C++ 98/11/20
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_SREADERS_DEFS_H
#define __VIC_SREADERS_DEFS_H

#include<__vic/_cfg.h>
#if __has_include(<concepts>)
#include<concepts>
#include<cstddef> // std::byte
#endif
#include<utility> // std::declval()

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Expected s-reader interface (concept)
//////////////////////////////////////////////////////////////////////////////
// template<class T>
// interface sreader
// {
//     sreader(sreader && ); or sreader(const sreader & );
//     sreader_result<T> auto operator()(); // throws on errors
// };
//////////////////////////////////////////////////////////////////////////////
// template<class T>
// interface sreader_result
// {
//     explicit operator bool() const; // Was the read successful (not EOF)?
//     T value() const; // The read result. Precondition: *this == true
// };
//////////////////////////////////////////////////////////////////////////////

#if __cpp_lib_concepts
//////////////////////////////////////////////////////////////////////////////
template<class R, class T>
concept sreader_result =
    std::semiregular<R> &&
    requires(R r) {
        bool{r};
        {r.value()} -> std::same_as<T>;
    };
//////////////////////////////////////////////////////////////////////////////
template<class R, class T>
concept sreader =
    std::movable<R> &&
    requires(R r) {
        {r()} -> sreader_result<T>;
    };
//////////////////////////////////////////////////////////////////////////////
template<class R, class T>
concept byte_sreader =
    sreader<R, T> && (
    std::same_as<T, unsigned char> ||
    std::same_as<T, char         > ||
    std::same_as<T, char8_t      > ||
    std::same_as<T, std::byte    >);
//////////////////////////////////////////////////////////////////////////////
#endif

//////////////////////////////////////////////////////////////////////////////
template<class SReaderResult>
struct sreader_value
{
#if __cpp_decltype
    typedef decltype(std::declval<SReaderResult>().value()) type;
#endif
};
#if __cpp_alias_templates
template<class SReaderResult>
using sreader_value_t = typename sreader_value<SReaderResult>::type;
#endif
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
