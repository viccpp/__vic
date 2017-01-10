// Windows-specific error handling and diagnostic utilities
//
// Platform: ISO C++ 98/11 - Win32
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_WINDOWS_ERROR_H
#define __VIC_WINDOWS_ERROR_H

#include<__vic/defs.h>
#include<__vic/static_string.h>
#include<exception>
#include<windef.h>

// To not include huge windows.h
extern "C" DWORD WINAPI GetLastError(void);

namespace __vic { namespace windows {

//////////////////////////////////////////////////////////////////////////////
// Utility for Win32 API native error handling like __vic::libc_error
//////////////////////////////////////////////////////////////////////////////
class error : public std::exception
{
    DWORD code_;
    mutable bool formatted;
    mutable static_string msg;
public:
    explicit error(DWORD = ::GetLastError());
    explicit error(const char * , DWORD = ::GetLastError());

    const char *what() const noexcept;
    DWORD code() const { return code_; }
};
//////////////////////////////////////////////////////////////////////////////

__VIC_NORETURN void throw_last_error(const char * );
__VIC_NORETURN void throw_last_error(const char * , DWORD );

}} // namespace

#endif // header guard
