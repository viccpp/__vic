// Generic utility for sequential one by one elements writing (output)
//
// Platform: ISO C++ 98/11/20
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_SWRITERS_DEFS_H
#define __VIC_SWRITERS_DEFS_H

#include<__vic/_cfg.h>
#if __has_include(<concepts>)
#include<concepts>
#endif

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Expected s-writer interface (concept)
//////////////////////////////////////////////////////////////////////////////
// template<class T>
// interace swriter
// {
//     swriter(swriter && ); or swriter(const swriter & );
//     void operator()(T ); // throws on errors
// };
//////////////////////////////////////////////////////////////////////////////

#if __cpp_lib_concepts
//////////////////////////////////////////////////////////////////////////////
template<class W, class T>
concept swriter =
    std::movable<W> &&
    requires(W w, const T v) {
        w(v);
    };
//////////////////////////////////////////////////////////////////////////////
#endif

} // namespace

#endif // header guard
