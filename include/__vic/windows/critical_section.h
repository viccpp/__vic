// C++ wrapper for Win32 API CRITICAL_SECTION
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_WINDOWS_CRITICAL_SECTION_H
#define __VIC_WINDOWS_CRITICAL_SECTION_H

#include<__vic/defs.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic { namespace windows {

//////////////////////////////////////////////////////////////////////////////
class CriticalSection : private non_copyable
{
    CRITICAL_SECTION cs;
public:
    CriticalSection() { ::InitializeCriticalSection(&cs); }
#if defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x0403
    explicit CriticalSection(DWORD dwSpinCount)
    {
        // Raises an exception on Win9x
        if(!::InitializeCriticalSectionAndSpinCount(&cs, dwSpinCount))
            throw_last_error("InitializeCriticalSectionAndSpinCount");
    }
#endif
    ~CriticalSection() { ::DeleteCriticalSection(&cs); }

    void Enter() { ::EnterCriticalSection(&cs); }
    bool TryEnter() { return ::TryEnterCriticalSection(&cs); }
    void Leave() noexcept { ::LeaveCriticalSection(&cs); }

    CRITICAL_SECTION *handle() { return &cs; }
    const CRITICAL_SECTION *handle() const { return &cs; }
};
//////////////////////////////////////////////////////////////////////////////
// Critical section guard
//////////////////////////////////////////////////////////////////////////////
class CSGuard : private non_copyable
{
    CRITICAL_SECTION &cs;
    void lock_() { ::EnterCriticalSection(&cs); }
public:
    enum adopt_t { adopt };

    explicit CSGuard(CRITICAL_SECTION &cs) : cs(cs) { lock_(); }
    CSGuard(CRITICAL_SECTION &cs, adopt_t) : cs(cs) {}

    explicit CSGuard(CriticalSection &cs) : cs(*cs.handle()) { lock_(); }
    CSGuard(CriticalSection &cs, adopt_t) : cs(*cs.handle()) {}

    ~CSGuard() { ::LeaveCriticalSection(&cs); }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
