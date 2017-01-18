// Internal implementation header
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_THROW_ERRNO_H
#define __VIC_THROW_ERRNO_H

#include<__vic/defs.h>

namespace __vic {

__VIC_NORETURN void throw_errno(const char * );
__VIC_NORETURN void throw_errno(const char * , int );

} // namespace

#endif // header guard
