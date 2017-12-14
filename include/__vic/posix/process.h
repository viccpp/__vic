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
#if __cpp_initializer_lists
#include<initializer_list>
#endif

namespace __vic { namespace posix {

// BSD daemon() call
void daemon(bool , bool = false);

// true if process associated with the PID exists and not a zombie
bool process_alive(pid_t );

void ignore_signals(const int [], size_t );
//----------------------------------------------------------------------------
template<size_t Size>
inline void ignore_signals(const int (&sigs)[Size])
{
    ignore_signals(sigs, Size);
}
//----------------------------------------------------------------------------
#if __cpp_initializer_lists
inline void ignore_signals(std::initializer_list<int> sigs)
{
    ignore_signals(sigs.begin(), sigs.size());
}
#endif
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
