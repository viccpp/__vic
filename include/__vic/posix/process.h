// Process-related tools
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_POSIX_PROCESS_H
#define __VIC_POSIX_PROCESS_H

#include<__vic/defs.h>

namespace __vic { namespace posix {

// BSD daemon() call
void daemon(bool , bool = false);

}} // namespace

#endif // header guard
