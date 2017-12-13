// Process-related tools
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_POSIX_PROCESS_H
#define __VIC_POSIX_PROCESS_H

#include<__vic/defs.h>
#include<sys/types.h>

namespace __vic { namespace posix {

// BSD daemon() call
void daemon(bool , bool = false);

// true if process associated with the PID exists and not a zombie
bool process_alive(pid_t );

}} // namespace

#endif // header guard
