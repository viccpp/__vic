// C++ wrappers for Win32 API HANDLE
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_WINDOWS_HANDLE_H
#define __VIC_WINDOWS_HANDLE_H

#include<__vic/defs.h>
#include __VIC_SWAP_HEADER
#include<exception>
#include<windows.h>

namespace __vic { namespace windows {

//////////////////////////////////////////////////////////////////////////////
class Handle
{
    HANDLE h;
public:
    Handle() __VIC_DEFAULT_CTR // uninitialized
    __VIC_CONSTEXPR_FUNC Handle(HANDLE h) : h(h) {}

    bool CloseNT() noexcept { return ::CloseHandle(h); }
    bool Wait(DWORD = INFINITE);

    bool IsInvalid() const { return h == INVALID_HANDLE_VALUE; }
    void SetInvalid() { h = INVALID_HANDLE_VALUE; }
    operator HANDLE() const { return h; }

    void swap(Handle &o) noexcept { std::swap(h, o.h); }
};
//////////////////////////////////////////////////////////////////////////////
struct WaitAbandoned : public std::exception
{
    const char *what() const noexcept;
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
