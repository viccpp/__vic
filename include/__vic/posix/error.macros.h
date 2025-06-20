// POSIX-specific error handling macros, mainly for using with C++ modules
//
// Platform: ISO C++ 98
// $Id$
//
// (c) __vic 2025

#ifndef __VIC_POSIX_ERROR_MACROS_H
#define __VIC_POSIX_ERROR_MACROS_H

#include<cerrno>

#if defined(ESTALE) && ESTALE != ENOENT
// ESTALE - Stale NFS file handle
#define __VIC_CASE_ENOENT case ENOENT: case ESTALE:
#else
#define __VIC_CASE_ENOENT case ENOENT:
#endif

#if defined(EWOULDBLOCK) && EWOULDBLOCK != EAGAIN
#define __VIC_CASE_EAGAIN case EAGAIN: case EWOULDBLOCK:
#else
#define __VIC_CASE_EAGAIN case EAGAIN:
#endif

#endif // header guard
