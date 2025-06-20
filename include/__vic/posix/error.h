// POSIX-specific error handling and diagnostic utilities
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2013

#ifndef __VIC_POSIX_ERROR_H
#define __VIC_POSIX_ERROR_H

#include<__vic/defs.h>
#include<__vic/error.macros.h>

namespace __vic { namespace posix {

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
