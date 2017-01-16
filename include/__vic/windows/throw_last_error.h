// Internal implementation header
//
// Platform: ISO C++ 98/11 - Win32
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_WINDOWS_THROW_LAST_ERROR_H
#define __VIC_WINDOWS_THROW_LAST_ERROR_H

#include<__vic/defs.h>
#include<windef.h>

namespace __vic { namespace windows {

__VIC_NORETURN void throw_last_error(const char * );
__VIC_NORETURN void throw_last_error(const char * , DWORD );

}} // namespace

#endif // header guard
