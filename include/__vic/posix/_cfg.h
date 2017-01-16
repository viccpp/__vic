// Internal header. POSIX-related defines
//
// __VIC_POSIX_TMO__ - POSIX timeouts are enabled
//                     Issue 6 feature. Derived from IEEE Std 1003.1d-1999
// __VIC_POSIX_BAR__ - POSIX barriers are enabled
//                     Issue 6 feature. Derived from IEEE Std 1003.1j-2000
// __VIC_POSIX_XSI__ - POSIX XSI extension is enabled
// __VIC_POSIX_RT__  - POSIX Realtime Extension ("POSIX.1")
//                     IEEE Std 1003.1b-1993/1003.1i-1995/1003.1-2004
//
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_POSIX__CFG_H
#define __VIC_POSIX__CFG_H

#include<__vic/_cfg.h>
#include<unistd.h>

//////////////////////////////////////////////////////////////////////////////
#if defined(__linux__)

#ifdef __USE_XOPEN2K
#define __VIC_POSIX_TMO__ 1
#define __VIC_POSIX_BAR__ 1
#endif

#ifdef __USE_UNIX98
#define __VIC_POSIX_XSI__ 1
#endif

#ifdef __USE_POSIX199309
#define __VIC_POSIX_RT__ 1
#endif

//////////////////////////////////////////////////////////////////////////////
#elif defined(__FreeBSD__)

#define __VIC_POSIX_TMO__   1
#define __VIC_POSIX_BAR__   1
#define __VIC_POSIX_XSI__   1

#if __FreeBSD__ >= 7
#define __VIC_POSIX_RT__ 1
#endif

//////////////////////////////////////////////////////////////////////////////
#elif defined(__hpux)

#ifdef _INCLUDE_POSIX4_SOURCE
#define __VIC_POSIX_RT__ 1
#endif

//////////////////////////////////////////////////////////////////////////////
#elif defined(_AIX)

#if _XOPEN_SOURCE >= 600
#define __VIC_POSIX_TMO__   1
#define __VIC_POSIX_BAR__   1
#endif
#ifndef _AIX_PTHREADS_D7
#define __VIC_POSIX_XSI__   1
#endif

#endif // OS
//////////////////////////////////////////////////////////////////////////////

#endif // header guard
