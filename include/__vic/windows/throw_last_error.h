// Internal implementation header
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_WINDOWS_THROW_LAST_ERROR_H
#define __VIC_WINDOWS_THROW_LAST_ERROR_H

#include<__vic/defs.h>

namespace __vic { namespace windows {

// The second parameter is actually DWORD
// but including big header only for one typedef is an overkill
__VIC_NORETURN void throw_last_error(const char * );
__VIC_NORETURN void throw_last_error(const char * , unsigned );
__VIC_NORETURN void throw_failed(const char * );

}} // namespace

#endif // header guard
