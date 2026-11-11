// Internal header. POSIX-related defines
//
// __VIC_POSIX_TMO__ - POSIX timeouts are enabled
//                     Issue 6 feature. Derived from IEEE Std 1003.1d-1999
// __VIC_POSIX_BAR__ - POSIX barriers are enabled
//                     Issue 6 feature. Derived from IEEE Std 1003.1j-2000
// __VIC_POSIX_XSI__ - POSIX XSI extension is enabled
//
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_POSIX__CFG_H
#define __VIC_POSIX__CFG_H

#include<__vic/_cfg.h>
#include<unistd.h>

#if defined(_POSIX_TIMEOUTS) && _POSIX_TIMEOUTS >= 0
#define __VIC_POSIX_TMO__ 1
#endif

#if defined(_POSIX_BARRIERS) && _POSIX_BARRIERS >= 0
#define __VIC_POSIX_BAR__ 1
#endif

#if defined(_XOPEN_UNIX) && _XOPEN_UNIX != -1
#define __VIC_POSIX_XSI__ 1
#endif

#endif // header guard
