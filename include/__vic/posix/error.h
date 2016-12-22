// POSIX-specific error handling and diagnostic utilities
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2013

#ifndef __VIC_POSIX_ERROR_H
#define __VIC_POSIX_ERROR_H

#include<cerrno>

namespace __vic { namespace posix {

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

//----------------------------------------------------------------------------
inline bool is_ENOENT(int err_no)
{
    switch(err_no) { __VIC_CASE_ENOENT return true; }
    return false;
}
//----------------------------------------------------------------------------
inline bool is_EAGAIN(int err_no)
{
    switch(err_no) { __VIC_CASE_EAGAIN return true; }
    return false;
}
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
