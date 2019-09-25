// Memory-related utilities
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2019

#ifndef __VIC_MEMORY_H
#define __VIC_MEMORY_H

#include<__vic/defs.h>

namespace __vic {

//----------------------------------------------------------------------------
template<class T>
inline T load_unaligned(const void *p)
{
#ifdef __VIC_STRICT_RAM_ALIGNMENT__
#ifdef __GNUC__
    struct wrapper { T v; } __attribute__((packed));
    return static_cast<const wrapper *>(p)->v;
#else
#   error Add unaligned access implementation for your compiler/platform
#endif
#else // unaligned access is OK
    return *static_cast<const T *>(p);
#endif
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
